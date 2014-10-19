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
#include <functional>

using CoilsFiller = std::function<cv::Point(int)>;

class Transformer
{
public:
    Transformer(int width, int coilsCount, CoilsFiller);
    virtual ~Transformer();

    cv::Point convert(int x, int y) const;
    bool isReady() const;

    const std::vector<cv::Point>& getCoils() const;
    int getWidth() const;

private:
    std::vector<cv::Point> _coils;
    int _width = 0;
};

#endif /* TRANSFORMER_H_ */
