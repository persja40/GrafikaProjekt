#pragma once

#include "Image.h"
#include "InterpolationModes.h"
#include "Size.h"
#include "defines.h"
#include "Matrix2D.h"

namespace ImageTransformator {
	Image applyScaleAndCentralRotation(const Image & sourceImage, float angle, float sx, float sy, InterpolationModes interpolationMode = InterpolationModes::bilinear);
	Image applyScaleAndCentralRotation(const Image & sourceImage, float angle, const Size & targetImageSize, float sx,float sy, InterpolationModes interpolationMode = InterpolationModes::bilinear);
		
	Image rescaleImage(Image & sourceImage,const Size & targetSize,InterpolationModes interpolationMode = InterpolationModes::bilinear);
}
