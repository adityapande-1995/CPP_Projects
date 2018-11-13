#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>

Eigen::MatrixXd sigmoid(Eigen::MatrixXd mat){
    int r = mat.rows() ; int c = mat.cols();
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            mat(i,j) = 1/(1+exp(-mat(i,j)));
        }
    }
    return mat;
};


class NeuralNetwork{
    public:
    std::vector <Eigen::MatrixXd> biases;
    std::vector <Eigen::MatrixXd> weights;
    int num_layers;
    std::vector <int> sizes;

    NeuralNetwork(std::vector <int> Sizes){
        num_layers = Sizes.size();
        sizes = Sizes;

        // Initializing random biases
        // std::cout<< "Initializing bases"<< std::endl;
        for (int i=1; i<sizes.size(); i++){
            int y = sizes[i];
            auto m = Eigen::MatrixXd::Random(y,1);
            biases.push_back(m);
            // std::cout<< "Shape : "<<y << " "<< 1 << std::endl;
        }

        // Initializing random weights
        // std::cout<< "Initializing weights"<< std::endl;
        for (int i=0; i<sizes.size()-1; i++){
            int x = sizes[i] ; int y = sizes[i+1];
            auto m = Eigen::MatrixXd::Random(y,x);
            weights.push_back(m);
            // std::cout<< "Shape : "<<y<< " "<<x<< std::endl;
        }
    };

    Eigen::MatrixXd predict(Eigen::MatrixXd input){
        for (int i=0; i<biases.size(); i++){
            input = sigmoid((weights[i]*input) + biases[i]);
        }

        return input;
    };

};
