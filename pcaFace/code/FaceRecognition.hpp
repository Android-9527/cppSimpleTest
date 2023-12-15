#ifndef FACERECOG
#define FACERECOG

#include <opencv2/opencv.hpp>
#include <vector>

class FaceRecognition {
public:
    // 构造函数
    FaceRecognition();
    FaceRecognition(const cv::Mat& reduced) : reducedData(reduced) {}

    // 查询函数
    std::vector<std::pair<int, double>> recognize(const int query) {
        // 这里实现人脸识别的逻辑，可以使用余弦相似度或其他方法

        // 计算查询人脸与数据库中所有人脸的相似度
        std::vector<std::pair<int, double>> similarityScores;
        //std::cout<<"redcrows "<<reducedData.rows<<std::endl;
        for (int i = 0; i < reducedData.rows; ++i) {
            double similarity = cosineSimilarity(reducedData.row(query), reducedData.row(i));
            similarityScores.push_back(std::make_pair(i, similarity));
        }

        // 按相似度降序排序
        std::sort(similarityScores.rbegin(), similarityScores.rend(), [](const auto& lhs, const auto& rhs) {
            return lhs.second < rhs.second;
        });

        // for(auto match:similarityScores){
        //     int index = match.first;
        //     double similarity = match.second;
        //     std::cout << "索引：" << index << ", 相似度：" << similarity << std::endl;
        // }
        // 选择前 10 个最相似的人脸
        int topN = 10;
        std::vector<std::pair<int, double>> topMatches(similarityScores.begin(), similarityScores.begin() + topN);

        return topMatches;
    }

private:
    cv::Mat reducedData;  // 存储降维后的人脸数据
    
    

    // 计算余弦相似度
    double cosineSimilarity(const cv::Mat& vec1, const cv::Mat& vec2) {
        double dotProduct = vec1.dot(vec2);
        double normVec1 = cv::norm(vec1);
        double normVec2 = cv::norm(vec2);

        return dotProduct / (normVec1 * normVec2);
    }
};

#endif  //FACERECOG