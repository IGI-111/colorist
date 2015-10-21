#ifndef PIXMAP_H_SPXEH8AS
#define PIXMAP_H_SPXEH8AS

#include <string>
#include "color.h"
#include "matrix.h"

// PBM format (monochrome)
Matrix<Color> readMonochrome(const std::string &filename);
Matrix<Color> randomMonochrome(const unsigned width, const unsigned height);

// PPM format (full-color)
void writeColored(const Matrix<Color> &bitmap, const std::string &filename);


#endif /* end of include guard: PIXMAP_H_SPXEH8AS */
