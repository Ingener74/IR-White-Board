/*
 * Transformer.h
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#ifndef TRANSFORMER_H_
#define TRANSFORMER_H_

#include <opencv2/core/core.hpp>
#include <vector>

using CoilsFiller = std::function<cv::Point(int)>;

class Transformer
{
public:
    Transformer(int width, int coilsCount, CoilsFiller);
    virtual ~Transformer() = default;

    cv::Point convert(int x, int y);

private:
    std::vector<cv::Point> _coils;
    int _width = 0;
};

#endif /* TRANSFORMER_H_ */
