#pragma once

#include "Image.h"
#include "InterpolationModes.h"
#include "defines.h"
#include "Matrix2D.h"


namespace ImageTransformator {
	Image applyScaleAndCentralRotation(const Image & sourceImage, float angle, float sx, float sy, InterpolationModes interpolationMode = InterpolationModes::bilinear);
	Image applyScaleAndCentralRotation(const Image & sourceImage, float angle, const sf::Vector2i & targetImageSize, float sx,float sy, InterpolationModes interpolationMode = InterpolationModes::bilinear);
		
	Image rescaleImage(Image & sourceImage,const sf::Vector2i & targetSize,InterpolationModes interpolationMode = InterpolationModes::bilinear);
}
