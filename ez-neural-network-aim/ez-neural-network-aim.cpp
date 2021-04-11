#include <opencv2/opencv.hpp>
#include "screenshot.h"
#include "detector.h"
#include <filesystem>
#include "defines.h"

std::wstring current_dir() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}

int main() {
    screenshot screen;
    cv::Mat image = screen.get();
    const std::wstring current_directory = current_dir();
    const std::string str_exe_path(current_directory.begin(), current_directory.end());

    detector detect(
        str_exe_path + "\\" + LABELS_FILE_NAME,
        str_exe_path + "\\" + YOLO_CFG_FILE_NAME,
        str_exe_path + "\\" + YOLO_WEIGHTS_FILE_NAME
    );

    Sleep(1000);

    while (true) {
        image = screen.get();
        detect.start(image);
        cv::waitKey(1);
    }

    return 0;
}


