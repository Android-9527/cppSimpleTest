#include <iostream>
#include <eigen3/Eigen/Dense>
#include <chrono>
#include <random>
using namespace Eigen;

class KalmanFilter {
public:
    KalmanFilter(double initial_position, double initial_velocity, double process_variance, double measurement_variance)
        : state_estimate_(Vector2d(initial_position, initial_velocity)),
          estimate_error_(Matrix2d::Identity()),
          process_variance_(Matrix2d::Identity() * process_variance),
          measurement_variance_(measurement_variance) 
          {
            H_<< 1,0;
            A_ <<1,1,0,1;
          }

    void update(double control_input, double measurement) {
        // 预测步骤
        Vector2d predicted_state = A_ * state_estimate_ + B_ * control_input;
        Matrix2d predicted_estimate_error = A_ * estimate_error_ * A_.transpose() + process_variance_;

        // 更新步骤
        Eigen::Matrix<double, 2, 1> kalman_gain = predicted_estimate_error * H_.transpose() / (H_ * predicted_estimate_error * H_.transpose() + measurement_variance_);
        state_estimate_ = predicted_state + kalman_gain * (measurement - H_ * predicted_state);
        estimate_error_ = (Matrix2d::Identity() - kalman_gain * H_) * predicted_estimate_error;

        // 输出当前估计值
        std::cout << "Position Estimate: " << state_estimate_(0) << ", Velocity Estimate: " << state_estimate_(1) << std::endl;
    }

private:
    Vector2d state_estimate_;      //X 状态估计值 [position, velocity] 
    Matrix2d estimate_error_;      //P 估计误差协方差矩阵 
    Matrix2d process_variance_;    //Q 过程噪声协方差矩阵
    double measurement_variance_;  //R 测量噪声方差

    // 状态转移矩阵 A
    Matrix2d A_ = Matrix2d::Identity();
    
    // 控制输入矩阵 B （如果没有外部控制输入，可以为零矩阵）
    Vector2d B_ = Vector2d::Zero();
    
    // 测量矩阵 H
    Eigen::Matrix<double, 1, 2> H_;
    //Matrix<double, 2, 2> H_ = Matrix<double, 2, 2>::Identity();

};

int main() {
    // 创建卡尔曼滤波器
    
    
    KalmanFilter kf(0.0, 0.0, 0.01, 1); // 初始位置为0，初始速度为1，过程噪声方差为0.01，测量噪声方差为0.1


    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // 模拟输入测量值，并进行卡尔曼滤波
    for (int i = 0; i < 100; ++i) {
        double control_input = 0; // 模拟外部控制输入
        std::default_random_engine generator(seed);
        std::normal_distribution<double> distribution(0, 1);
        double measurement = i + distribution(generator); // 模拟测量值，加入一些随机噪声
        kf.update(control_input, measurement);
    }

    return 0;
}





