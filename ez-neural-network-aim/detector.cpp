#include "detector.h"


void detector::draw_box(float conf, int left, int top, int right, int bottom, cv::Mat& frame) {
    cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(0, 0, 255));
    std::string label = cv::format("%.2f", conf);
    putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255));
}

std::vector<cv::String> detector::get_outputs_names(const cv::dnn::Net& net) {
    static std::vector<cv::String> names;
    if (names.empty()) {
        std::vector<int> outLayers =
            net.getUnconnectedOutLayers();
        std::vector<cv::String> layersNames =
            net.getLayerNames();
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
            names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}

void detector::postprocess(cv::Mat& frame, const std::vector<cv::Mat>& outs) {
    std::vector<int> classes_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    for (size_t i = 0; i < outs.size(); ++i) {
        float* data = (float*)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
            cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            cv::Point class_id_point;
            double confidence;
            cv::minMaxLoc(scores, 0, &confidence, 0, &class_id_point);
            if (confidence > m_confidence) {
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classes_ids.push_back(class_id_point.x);
                confidences.push_back((float)confidence);
                boxes.push_back(cv::Rect(left, top, width, height));
            }
        }
    }

    // exclusion of overlapping boxes and other trash
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, m_confidence, m_threshold, indices);

    for (size_t i = 0; i < indices.size(); ++i) {
        int idx = indices[i];
        cv::Rect box = boxes[idx];
        draw_box(confidences[idx], box.x, box.y,
            box.x + box.width, box.y + box.height, frame);

        // todo: check if the aim is enabled
        aimbot::aim_to(box.x, box.y, box.width, box.height);
    }

    return;
}


static clock_t current_ticks, delta_ticks;
static clock_t fps = 0;

void detector::start(cv::Mat& image) {
    current_ticks = clock();

    cv::Mat blob;
    cv::dnn::blobFromImage(image, blob, 1 / 255.0,
        cv::Size(m_activation_range, m_activation_range), cv::Scalar(0, 0, 0), true, false);
    m_net.setInput(blob);
    std::vector<cv::Mat> outs;
    m_net.forward(outs, get_outputs_names(m_net));

    postprocess(image, outs);

    std::string label = cv::format("FPS: %u", (unsigned int)fps);
    cv::putText(image, label, cv::Point(0, 15),
        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));

    cv::Mat detected_frame;
    image.convertTo(detected_frame, CV_8U);
    cv::imshow("NN", detected_frame);

    // number of processed frames per sec.
    delta_ticks = clock() - current_ticks;
    if (delta_ticks > 0)
        fps = CLOCKS_PER_SEC / delta_ticks;

    return;
}


detector::detector(std::string dataset_labels_path, std::string yolo_config_path, std::string yolo_weights_path) {
    std::string line;
    std::ifstream file_labels(dataset_labels_path.c_str());

    m_activation_range = static_cast<int>(ACTIVATION_RANGE / 2);

    while (std::getline(file_labels, line))
        m_classes.push_back(line);

    m_net = cv::dnn::readNetFromDarknet(yolo_config_path, yolo_weights_path);
    m_net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
    m_net.setPreferableTarget(cv::dnn::DNN_TARGET_OPENCL);

    
    if (cv::ocl::haveOpenCL()) {
        cv::ocl::setUseOpenCL(true);
        cv::ocl::useOpenCL();
    }
}