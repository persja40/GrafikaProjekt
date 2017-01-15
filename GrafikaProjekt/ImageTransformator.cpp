#include "ImageTransformator.h"

Image ImageTransformator::applyScaleAndCentralRotation(const Image & sourceImage, float angle, float sx, float sy, InterpolationModes interpolationMode)
{
	int w = abs(((float)sourceImage.getHeight())*sin(angle)) + abs(((float)sourceImage.getWidth())*cos(angle));
	int h = abs(((float)sourceImage.getHeight())*cos(angle)) + abs(((float)sourceImage.getWidth())*sin(angle));
	
	sf::Vector2i targetImageSize = sf::Vector2i(w*sx, h*sx);
	return ImageTransformator::applyScaleAndCentralRotation(sourceImage, angle, targetImageSize, sx, sy, interpolationMode);
}

Image ImageTransformator::applyScaleAndCentralRotation(const Image & sourceImage, float angle, const sf::Vector2i & targetImageSize, float sx, float sy, InterpolationModes interpolationMode)
{
	
	Matrix2D transformationMatrix;
	Matrix2D rotation = Matrix2D::getRotationMatrix(angle);
	Matrix2D translation = Matrix2D::getTranslationMatrix((float)sourceImage.getWidth() / 2.0, (float)sourceImage.getHeight() / 2.0);
	Matrix2D reverseTranslation = Matrix2D::getTranslationMatrix(-(float)targetImageSize.x / 2.0, -(float)targetImageSize.y / 2.0);
	Matrix2D scale = Matrix2D::getScaleMatrix(1/sx, 1/sy);

	Image resultImage(targetImageSize.x, targetImageSize.y);

	transformationMatrix = translation*scale*rotation*reverseTranslation;

	// for fast counting
	float * translationArray = transformationMatrix.getMatrixArrayCopy();

	int sourceW,sourceH,targetW,targetH;

	sourceH = sourceImage.getHeight();
	sourceW = sourceImage.getWidth();
	targetW = targetImageSize.x;
	targetH = targetImageSize.y;

	uint32_t * sourcePixmap = (uint32_t *) sourceImage.getPixmap();
	uint32_t * destPixmap = (uint32_t *) resultImage.getPixmap();
	
	if (interpolationMode == bilinear) {
		
		for (unsigned row=0; row < targetImageSize.y; row++) {
			float sourceX, sourceY, xDelta, yDelta;
			float rawColorTop[4], rawColorBottom[4], rawTotal[4];
			int xCeil, yCeil, yFloor, xFloor;
			uint8_t * leftTop, *leftBottom, *rightTop, *rightBottom, *resultColor;

			for (unsigned column=0; column < targetImageSize.x; column++) {
				
				sourceX = translationArray[0] * ((float)column) + translationArray[1] * ((float)row) + translationArray[2];
				sourceY = translationArray[3] * ((float)column) + translationArray[4] * ((float)row) + translationArray[5];

				// interpolation

				xCeil = sourceX+1;
				yCeil = sourceY+1;

				xFloor = sourceX;
				yFloor = sourceY;

				if (xCeil >= sourceW || yCeil >= sourceH || xFloor < 0 || yFloor < 0) {
					destPixmap[row*targetW + column] = 0;
					continue;
				}

				xDelta = ((float)xCeil)-((float)xFloor);
				yDelta = ((float)yCeil) -((float)yFloor);
				
				
				leftTop = (uint8_t *) (sourcePixmap + xFloor + sourceW*yCeil); 
				rightTop = (uint8_t *) (sourcePixmap + xCeil + sourceW*yCeil);
				leftBottom = (uint8_t *)(sourcePixmap + xFloor + sourceW*yFloor);
				rightBottom = (uint8_t *)(sourcePixmap + xCeil + sourceW*yFloor);
				
				// LERP 1 TOP
				rawColorTop[0] = ((float)leftTop[0])*(1.0 - xDelta) + ((float)rightTop[0])*xDelta;
				rawColorTop[1] = ((float)leftTop[1])*(1.0 - xDelta) + ((float)rightTop[1])*xDelta;
				rawColorTop[2] = ((float)leftTop[2])*(1.0 - xDelta) + ((float)rightTop[2])*xDelta;
				rawColorTop[3] = ((float)leftTop[3])*(1.0 - xDelta) + ((float)rightTop[3])*xDelta;

				// LERP 2 BOTTOM
				rawColorBottom[0] = ((float)leftBottom[0])*(1.0 - xDelta) + ((float)rightBottom[0])*xDelta;
				rawColorBottom[1] = ((float)leftBottom[1])*(1.0 - xDelta) + ((float)rightBottom[1])*xDelta;
				rawColorBottom[2] = ((float)leftBottom[2])*(1.0 - xDelta) + ((float)rightBottom[2])*xDelta;
				rawColorBottom[3] = ((float)leftBottom[3])*(1.0 - xDelta) + ((float)rightBottom[3])*xDelta;

				// LERP 3 BOTTOM <-> TOP 
				rawTotal[0] = rawColorTop[0] * (1.0-yDelta) + rawColorBottom[0] * yDelta;
				rawTotal[1] = rawColorTop[1] * (1.0 - yDelta) + rawColorBottom[1] * yDelta;
				rawTotal[2] = rawColorTop[2] * (1.0 - yDelta) + rawColorBottom[2] * yDelta;
				rawTotal[3] = rawColorTop[3] * (1.0 - yDelta) + rawColorBottom[3] * yDelta;

				// SAVE 

				destPixmap[row*targetW + column] = ((uint8_t) rawTotal[0]) | ((uint8_t) rawTotal[1])<<8 |((uint8_t) rawTotal[2])<<16 | ((uint8_t)rawTotal[3])<<24 ;
			}
		}
		delete[] translationArray;
		
	}

	return resultImage;
}

Image ImageTransformator::rescaleImage(Image & sourceImage, const sf::Vector2i & targetImageSize, InterpolationModes interpolationMode)
{
	float sx = (float)targetImageSize.x / (float)sourceImage.getWidth();
	float sy = (float)targetImageSize.y / (float)sourceImage.getHeight();

	return ImageTransformator::applyScaleAndCentralRotation(sourceImage, 0.0, targetImageSize,sx,sy, interpolationMode);
}
