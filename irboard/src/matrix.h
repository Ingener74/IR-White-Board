/*
 * matrix.h
 *
 *  Created on: 15.07.2012
 *      Author: Ingener
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <utility>

#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

template <typename T>
class matrix {
public:
	vector<T> matrix_data;
	Size_<unsigned int>	matrix_size;

	matrix( Size_<unsigned int> asize = Size_<unsigned int>(0, 0) ):matrix_data(asize.height*asize.width), matrix_size(asize){}

	T& get_element(unsigned int c, unsigned int r){
		return matrix_data[r*matrix_size.width + c];
	}

	void set_element(unsigned int c, unsigned int r, T value){
		matrix_data[r*matrix_size.width + c] = value;
	}
};

#endif /* MATRIX_H_ */
