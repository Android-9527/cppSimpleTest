#include <iostream>
#include <eigen3/Eigen/Dense>
class kal{
    public:
    kal(){}
    private:
    //Eigen::MatrixXd A(2, 2);
    Eigen::Matrix<double,1,2> H_;
    // A << 1, 2, 3, 4;

};
int main() {
    // 创建矩阵
    Eigen::MatrixXd A(2, 2);
    A =Eigen::Matrix2d::Identity();

    Eigen::MatrixXd B(2, 2);
    B << 5, 6, 7, 8;
    
    Eigen::MatrixXd H_(1, 2);
    H_ << 1,0;



    // 打印矩阵
    std::cout << "Matrix A:\n" << A << "\n\n";
    std::cout << "Matrix B:\n" << B << "\n\n";

    // 矩阵加法
    Eigen::MatrixXd C = A + B;
    std::cout << "Matrix A + B:\n" << C << "\n\n";

    // 矩阵减法
    Eigen::MatrixXd D = A - B;
    std::cout << "Matrix A - B:\n" << D << "\n\n";

    // 矩阵乘法
    Eigen::MatrixXd E = A * B;
    std::cout << "Matrix A * B:\n" << E << "\n\n";

    // 矩阵除法（逆矩阵乘法）
    Eigen::MatrixXd F = A * B.inverse();
    std::cout << "Matrix A / B:\n" << F << "\n\n";

    return 0;
}
