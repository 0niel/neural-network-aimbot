#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/core/ocl.hpp"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "defines.h"
#include "aimbot.h"

class detector {
public:
	detector(std::string dataset_labels_path, std::string yolo_config_path, std::string yolo_weights_path);
	~detector() { };
	void start(cv::Mat& image);

private:
	void postprocess(cv::Mat& frame, const std::vector<cv::Mat>& outs);
	void draw_box(float conf, int left, int top, int right, int bottom, cv::Mat& frame);
	std::vector<cv::String> get_outputs_names(const cv::dnn::Net& net);

	cv::dnn::Net m_net;
	float m_confidence = 0.5f;
	float m_threshold = 0.35f;
	int m_activation_range = 125;
	std::vector<std::string> m_classes;
};