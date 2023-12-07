#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include "MYPCA.hpp"
#include "FaceRecognition.hpp"
using namespace std;

//两层循环，字符串相加得到imgPaths
//遍历读取文件，拍扁存储到vector <Mat>中
//对数据进行处理8-bits uchar->32-bits f，并且减去每个维度的平均值
//pca




int main()
{
    std::string curPath="../FaceDB_orl/";
    vector<string> imgPaths=getImagPaths(curPath);
    //if you wnat predict you image
    cout<<"path import success"<<endl;
    // Vector to store flattened images
    std::vector<cv::Mat> flattenedImages;
    read_FlatImags(flattenedImages,imgPaths);
    cout<<"read and flatted !"<<endl; 
    
    // Perform PCA
    MyPCA myPCA(flattenedImages);
    cv::Mat reduced=myPCA.reduceDimension(400);
    myPCA.reconstructData();
    
    FaceRecognition faceRcg(reduced);
    while(1){
        int query;
        std::cout<<"input query number: "<<std::endl;
        std::cin>>query;
        if(query==-1) break;
        std::vector<std::pair<int, double>> labels=faceRcg.recognize(query);
            // 处理识别结果
        std::cout << "最相似的前十个人脸：" << std::endl;
        for (const auto& match : labels) {
            int index = match.first;
            double similarity = match.second;
            std::cout << imgPaths[index] << ", 相似度：" << similarity << std::endl;

            // 在这里你可以根据索引获取数据库中相似的人脸图像并显示或处理
        }


    }
    return 0;
}


    



