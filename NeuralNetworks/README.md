# Neural networks with Eigen

## Introduction
This is an attempt to write my own neural networks using the Eigen matrix library as a base.

## Usage
Have a look at main.cpp for the API. It can be compiled and run by executing :
```
make all && make run
```
Sample statements:
```cpp
auto s = std::vector <int> {2,5,3};
auto a = NeuralNetwork(s); // NN with 2,5,3 layers. 2 inputs, 3 outputs

auto inp = Eigen::MatrixXd::Random(2,1); // Supply random input
auto ans = a.predict(inp);
std::cout<< ans << std::endl;
```

## To do
* Backpropagation
* Different activation functions
* Training using neuroevolution
