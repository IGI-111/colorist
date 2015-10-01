#ifndef PIXMAP_H_SPXEH8AS
#define PIXMAP_H_SPXEH8AS

#include <string>
#include "color.h"

// PBM format (monochrome)
ColorMatrix readMonochrome(const std::string &filename);
ColorMatrix randomMonochrome(const unsigned width, const unsigned height);

// PPM format (full-color)
void writeColored(const ColorMatrix &bitmap, const std::string &filename);


#endif /* end of include guard: PIXMAP_H_SPXEH8AS */
