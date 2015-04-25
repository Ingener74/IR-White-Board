//
// Created by Pavel on 24.04.2015.
//

#ifndef PROJECT_IMAGEOUTPUT_H
#define PROJECT_IMAGEOUTPUT_H

#ifdef SWIG
    %feature("director") ImageOutput;
#else
    #include <cstdint>
#endif

class ImageOutput {
public:
    ImageOutput() { }
    virtual ~ImageOutput() { }

    virtual void updateImage(void* data, size_t width, size_t height) = 0;
};


#endif //PROJECT_IMAGEOUTPUT_H
