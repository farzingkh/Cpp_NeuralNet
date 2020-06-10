#include "../include/NN.h"
#include <assert.h>
#include <iostream>
int main()
{
    // Example with 2x2 matrix calculations
    typedef Eigen::Matrix<int, 2, 2> mat22i;
    typedef Eigen::Matrix<int, 1, 2> mat12i;
    typedef Eigen::Matrix<int, 2, 1> mat21i;

    NN nn = NN();

    mat22i A;
    A << 1, 2, 1, 2;

    mat22i B;
    B << 1, 1, 1, 1;

    mat22i C;
    C << 3, 3, 3, 3;

    Eigen::Matrix<int, 1, 1> i;
    i << 1;

    mat12i D;
    D << 1, 1;

    Eigen::Matrix<int, 1, 2> F;
    F << 1, 1;

    Eigen::Matrix<int, 1, 2> X;
    X << 3, 2;

    matXXi x = X.transpose();

    //auto C = nn.multiply<float,int,float>(nn.variable<int>(3),(nn.add<float,int,float>(nn.add<int,int,int>(nn.variable<int>(1),nn.variable<int>(2)), nn.negative<float>(nn.add<float,float,float>(nn.variable<float>(2.5),nn.variable<float>(1.5))))));
    //auto D = nn.multiply<mat, mat, mat>(nn.variable<mat>(std::move(B)), nn.negative<mat>(nn.variable<mat>(std::move(A))));

    // Define X * (-A) with X as a placeholder to feed later
    //auto D = nn.multiply<mat22i, mat22i, mat22i>(nn.placeholder<mat22i>("B"), nn.negative<mat22i>(nn.variable<mat22i>(std::move(A))));

    // Define A+(i*B) broadcasting i to size A
    //auto E = nn.add<mat22i, mat22i, mat22i>(nn.variable<mat22i>(std::move(A)), nn.multiply<mat22i, mat22i, int>(nn.variable<mat22i>(std::move(B)), nn.variable<int>(std::move(i))));

    auto G = nn.sigmoid<int>(nn.add<int>(nn.multiply<int>(nn.variable<int>(std::move(F)), nn.placeholder<int>("X")), nn.multiply<int>(nn.variable<int>(std::move(D)), nn.variable<int>(std::move(i)))));
    // Create map to feed data to the placeholders (i.e. X = B)
    //std::unordered_map<std::string, mat22i *> feed = {};
    //feed["B"] = &B;

    // Create map to feed data to the placeholders (i.e. X = X)
    std::unordered_map<std::string, matXXi *> feed = {};
    feed["X"] = &x;

    // Run the session and get the value of the operation
    int r = nn.run<int>(G, feed);

    std::cout << "Computational Operation Output:" << std::endl;
    std::cout << r << std::endl;
}