#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 创建一个示例图像数据（假设是 CV_8U 类型）
    cv::Mat uint8Image = cv::Mat::ones(64, 64, CV_8U) * 0;

    // 定义文件名
    std::string directoryPath = "../faDb/001";
   
    std::string fileName = "../code/06.png";

    // 尝试写入文件
    std::cout << "Attempting to write to file: " << fileName << std::endl;

    if (cv::imwrite(fileName, uint8Image)) {
        std::cout << "File write successful." << std::endl;
    } else {
        std::cerr << "Error writing file!" << std::endl;
    }

    return 0;
}
