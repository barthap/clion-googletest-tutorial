#include <iostream>
#include "matlab.hpp"
//
// Created by Barthap on 13.03.2018.
//

int MatVect::getElem(std::size_t pos) {
    return _v[pos];
}

void MatVect::setElem(std::size_t pos, int val) {
    _v[pos] = val;
}

unsigned long MatVect::size() {
    return _v.size();
}

MatVect add_vectors(MatVect v1, MatVect v2) {
    MatVect ret(v1.size());

    for(std::size_t i = 0; i < v1.size(); i++)
        ret.setElem(i, v1.getElem(i) + v2.getElem(i));

    return ret;
}

void print_vector(MatVect v) {
    for (std::size_t i = 0; i < v.size(); i++) {
        std::cout << v.getElem(i) << " ";
    }
}
