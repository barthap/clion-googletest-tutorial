//
// Created by Barthap on 13.03.2018.
//

#ifndef MATLAB_2_MATLAB_HPP
#define MATLAB_2_MATLAB_HPP

#include <utility>
#include <vector>

class MatVect
{
    std::vector<int> _v;
public:
    explicit MatVect(std::size_t numElems) : _v(numElems, 0) {}
    explicit MatVect(std::vector<int> vect) : _v(std::move(vect)) {}

    int getElem(std::size_t pos);
    void setElem(std::size_t pos, int val);
    unsigned long size();
};

MatVect add_vectors(MatVect v1, MatVect v2);
void print_vector(MatVect v);


#endif //MATLAB_2_MATLAB_HPP
