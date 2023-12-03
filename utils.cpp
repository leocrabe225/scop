#include <utils.hpp>

void printMat4(const glm::mat4& matrix, int precision = 6) {
    const float* matData = glm::value_ptr(matrix);

    std::cout << "Matrix 4x4:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // Set precision for floating-point output
            std::cout << std::fixed << std::setw(precision + 5) << std::setprecision(precision) << matData[i * 4 + j] << "\t";
        }
        std::cout << std::endl;
    }
}