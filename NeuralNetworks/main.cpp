#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "nn.cpp"

int main(){
    auto s = std::vector <int> {2,5,3};
    auto a = NeuralNetwork(s); // NN with 2,5,3 layers. 2 inputs, 3 outputs

    auto inp = Eigen::MatrixXd::Random(2,1); // Supply random input
    auto ans = a.predict(inp);
    std::cout<< ans << std::endl;
    
    return 0;
}