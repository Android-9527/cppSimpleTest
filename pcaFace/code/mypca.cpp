#include "MYPCA.hpp"

// 构造函数
MyPCA::MyPCA(const std::vector<cv::Mat>& flattenedImages) : flattenedImages(flattenedImages) {
    // 可以在这里进行一些初始化操作
    dataProcess();

}


// 获取降维后的数据
cv::Mat MyPCA::reduceDimension(int k) {
    // 在这里实现降维逻辑
    this->k=k;
    cv::Mat _, singularValues;
    cv::SVDecomp(data, singularValues, _, Vt);
    std::cout<<"Vt size:  "<<Vt.size()<<std::endl;
    //std::cout<<"befor "<<singularValues.size()<<std::endl;
    // 选择前k个主成分
    //cetered=uw(Vt)
    cv::Mat topK = Vt.rowRange(0, k);
    Vt=topK;
    // 投影数据到低维空间
    //cetered*V=uw,n*m->n*k
    cv::Mat reducedData = data * topK.t();
    std::cout << "Reduce success,Reduce size = "<<reducedData.size() << std::endl;
    data=reducedData;
    
    return reducedData;
    // 返回降维后的数据矩阵
}

// 恢复降维后的数据
cv::Mat MyPCA::reconstructData() {
    // 在这里实现恢复降维后的数据逻辑
    // std::cout<<data.size()<<std::endl;
    // std::cout<<Vt.size()<<std::endl;
    // std::cout<<meanRepeated.size()<<std::endl;
    data=data*Vt+meanRepeated;
    std::cout << "recov data size"<<data.size() << std::endl;
    
    const int imageRows = 64;
    const int imageCols = 64;

    std::string curPath="../reducedFaceDB/";
    std::vector<std::string> reducedimgPaths=getImagPaths(curPath);
    // 遍历每一行
    for (int i = 0; i < data.rows; ++i) {
        // 提取每一行数据
        cv::Mat rowData = data.row(i);

        // 将一维数据转换为图像矩阵
        cv::Mat imageMat(imageRows, imageCols, CV_32F, rowData.data);

        // 调整图像大小
        cv::resize(imageMat, imageMat, cv::Size(imageCols, imageRows));

        // 转换为 CV_8U 类型
        cv::Mat uint8Image;
        imageMat.convertTo(uint8Image, CV_8U);

        // 保存图像
        //std::cout<<reducedimgPaths[i]<<std::endl;
        std::string fileName = reducedimgPaths[i];
        
        cv::imwrite(fileName, uint8Image);
    }
    std::cout<<"images writen "<<std::endl;
    
    
    return data;
    // 返回恢复后的数据矩阵
}

// 计算协方差矩阵
void MyPCA::dataProcess() {

    std::vector<cv::Mat> flattenedImages32f; 
    for (const auto& mat : flattenedImages) { 
        cv::Mat floatMat; 
        mat.convertTo(floatMat, CV_32F);
        flattenedImages32f.push_back(floatMat);
    } 
    //8-bits uchar -> 32-bits f
    flattenedImages=flattenedImages32f;

    

    cv::vconcat(flattenedImages, data);
    std::cout<<"data : "<<data.size()<<std::endl;
    // 计算均值
    cv::Mat mean;
    cv::reduce(data, mean, 0, CV_REDUCE_AVG);
    std::cout<<"mean size :"<<mean.size()<<std::endl;
    meanRepeated = cv::repeat(mean, data.rows, 1);

    // 对每一行减去均值
    //std::cout << "here---" << std::endl;
    data = data - meanRepeated;
    //瞎了cv::Mat centered = data - mean;
    
    std::cout<<"mypca dataprocessed"<<std::endl;
    std::cout<<"processed data size :"<<data.size()<<std::endl;
}

// 计算特征值和特征向量
std::vector<std::string> getImagPaths(const std::string& curtPath){
    std::vector<std::string> imgPaths={};
    //if you wnat predict you image
    std::vector<int> imgLabels={};
    //string path="../FaceDB_orl/";
    for(int i=1;i<=40;i++){
       //page path
        std::string path=curtPath;
        //"../FaceDB_orl/";
        
        if(i<=9)
            path=path+"00"+std::to_string(i)+"/";
        else
            path=path+"0"+std::to_string(i)+"/";
        /* cout<<path<<endl; */
        //sub page path
        for(int j=1;j<=10;j++){
            std::string path2;
            if(j<10)
                path2=path+"0"+std::to_string(j)+".png";
            else
                path2=path+"10.png";

            /* cout<<path2<<endl; */
            imgPaths.push_back(path2);
        }
    }
    
    return imgPaths;
}

void read_FlatImags(std::vector<cv::Mat> &flattenedImages,const std::vector<std::string>&imgPaths ){
    for(const auto&path:imgPaths){
            cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);
            if (image.empty()) {
                std::cerr << "Failed to read image: " << path << std::endl;
                continue; // Skip to the next image if reading fails
            }
            cv::resize(image, image, cv::Size(64, 64));
            // Flatten the image to a one-dimensional vector
            cv::Mat flattenedImage = image.reshape(1, 1);
            //(channel,rows) ,row=1,only one row
            // Add the flattened image to the vector
            flattenedImages.push_back(flattenedImage);
    }

    return;
}