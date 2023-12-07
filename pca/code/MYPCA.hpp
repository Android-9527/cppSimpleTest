#ifndef MYPCA_H
#define MYPCA_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include<string>

class MyPCA {
public:
    // 构造函数
    MyPCA();
    MyPCA(const std::vector<cv::Mat>& flattenedImages);
    // 设置输入数据

    // 获取降维后的数据
    cv::Mat reduceDimension(int k);

    // 恢复降维后的数据
    cv::Mat reconstructData();
    
private:
    // 数据矩阵
    std::vector <cv::Mat> flattenedImages;
    cv::Mat data;
    cv::Mat Vt,meanRepeated; 
    int k;
    // 计算协方差矩阵
    void dataProcess();
};

std::vector<std::string> getImagPaths(const std::string& curtPath);
void read_FlatImags(std::vector<cv::Mat> &flattenedImages,const std::vector<std::string>&imgPaths );
#endif  // MYPCA_H
