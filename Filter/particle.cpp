#include <iostream>
#include <vector>
#include <random>
#include <chrono>
struct Particle {
    double position;
    double weight;
};

double stateTransition(double x, double u, double dt, double process_noise_std) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(0, process_noise_std);
    return x + u * dt + distribution(generator);
}

double observationModel(double x, double noise_std) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(0, noise_std);
    return x + distribution(generator);
}

void particleFilter(std::vector<Particle>& particles, double u, double dt, double observation, double process_noise_std, double observation_noise_std) {
    // 状态转移
    for (auto& particle : particles) {
        particle.position = stateTransition(particle.position, u, dt, process_noise_std);
    }

    // 计算观测概率密度并更新权重
    for (auto& particle : particles) {
        double observation_prob = 1.0 / (std::sqrt(2 * M_PI) * observation_noise_std) * 
                                  std::exp(-0.5 * std::pow((particle.position - observation) / observation_noise_std, 2));
        particle.weight = observation_prob;
    }

    // 归一化权重
    double sum_weights = 0.0;
    for (const auto& particle : particles) {
        sum_weights += particle.weight;
    }
    for (auto& particle : particles) {
        particle.weight /= sum_weights;
    }

    //重采样
    // std::vector<Particle> resampled_particles;
    // std::default_random_engine generator;
    // std::uniform_real_distribution<double> distribution(0.0, 1.0);
    // double cumulative_weight = 0.0;
    // double step = 1.0 / particles.size();

    // for (int i = 0; i < particles.size(); ++i) {
    //     cumulative_weight += particles[i].weight;
    //     while (cumulative_weight > step * i + distribution(generator)) {
    //         resampled_particles.push_back(particles[i]);
    //     }
    // }
    // // 更新粒子集合
    // particles = resampled_particles;
}

int main() {
    int num_particles = 10000;
    std::vector<Particle> particles(num_particles, {5.0, 1.0 / num_particles});

    int num_steps = 100;
    double true_position = 5.0;

    for (int t = 0; t < num_steps; ++t) {
        true_position = stateTransition(true_position, 1.0, 1.0, 0);
        double observation = observationModel(true_position, 1);
        std::cout<<observation<<std::endl;
        particleFilter(particles, 1.0, 1.0, observation, 0.1, 1);

        double estimated_position = 0.0;
        for (const auto& particle : particles) {
            estimated_position += particle.position * particle.weight;
        }

        std::cout << "Time Step " << t << ": True Position = " << true_position
                  << ", Estimated Position = " << estimated_position <<"  "<<true_position-estimated_position<< std::endl;
    }

    return 0;
}
