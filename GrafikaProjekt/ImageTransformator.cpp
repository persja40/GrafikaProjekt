#include "ImageTransformator.h"

Image ImageTransformator::applyScaleAndCentralRotation(const Image & sourceImage, float angle, float sx, float sy, InterpolationModes interpolationMode)
{
	int longest = sqrt(((float)(sourceImage.getHeight()*sourceImage.getHeight()))*sx*sx + ((float)(sourceImage.getWidth()*sourceImage.getWidth()))*sy*sy);

	
	Size targetImageSize = Size((int)longest, (int)longest);
	return ImageTransformator::applyScaleAndCentralRotation(sourceImage, angle, targetImageSize, sx, sy, interpolationMode);
}

Image ImageTransformator::applyScaleAndCentralRotation(const Image & sourceImage, float angle, const Size & targetImageSize, float sx, float sy, InterpolationModes interpolationMode)
{
	

	Matrix2D transformationMatrix;
	Matrix2D rotation = Matrix2D::getRotationMatrix(angle);
	Matrix2D translation = Matrix2D::getTranslationMatrix((float)sourceImage.getWidth() / 2.0, (float)sourceImage.getHeight() / 2.0);
	Matrix2D reverseTranslation = Matrix2D::getTranslationMatrix(-(float)targetImageSize.getX() / 2.0, -(float)targetImageSize.getY() / 2.0);
	Matrix2D scale = Matrix2D::getScaleMatrix(-1.0/sx, 1.0/sy);

	Image resultImage(targetImageSize.getX(), targetImageSize.getY());

	transformationMatrix = translation*scale*rotation*reverseTranslation;

	// for fast counting
	float * translationArray = transformationMatrix.getMatrixArrayCopy();

	int sourceW,sourceH,targetW,targetH;

	sourceH = sourceImage.getHeight();
	sourceW = sourceImage.getWidth();
	targetW = targetImageSize.getX();
	targetH = targetImageSize.getY();

	uint32_t * sourcePixmap = (uint32_t *) sourceImage.getPixmap();
	uint32_t * destPixmap = (uint32_t *) resultImage.getPixmap();
	
	if (interpolationMode == bilinear) {
		//#pragma omp parallel
		for (unsigned row=0; row < targetImageSize.getX(); row++) {
			float sourceX, sourceY, xDelta, yDelta;
			float rawColorTop[4], rawColorBottom[4], rawTotal[4];
			int xCeil, yCeil, yFloor, xFloor;
			uint8_t * leftTop, *leftBottom, *rightTop, *rightBottom, *resultColor;

			for (unsigned column=0; column < targetImageSize.getY(); column++) {
				
				sourceX = translationArray[0] * ((float)row) + translationArray[1] * ((float)column) + translationArray[2];
				sourceY = translationArray[3] * ((float)row) + translationArray[4] * ((float)column) + translationArray[5];

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

				/*
				rightTop = sourceImage.getPixel(xCeil, yCeil);
				leftBottom = sourceImage.getPixel(xFloor, yFloor);
				rightBottom = sourceImage.getPixel(xCeil, yFloor);
				leftTop = sourceImage.getPixel(xFloor, yCeil);
				*/

				
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

				//Color c = { (uint8_t)rawTotal[0]  , (uint8_t)rawTotal[1], (uint8_t)rawTotal[2]  , (uint8_t)rawTotal[3] };
				//resultImage.setPixel(row, column, c);
				destPixmap[row*targetW + column] = ((uint8_t) rawTotal[0]) | ((uint8_t) rawTotal[1])<<8 |((uint8_t) rawTotal[2])<<16 | ((uint8_t)rawTotal[3])<<24 ;
			}
		}
		
		
	}

	
	return resultImage;
}

Image ImageTransformator::rescaleImage(Image & sourceImage, const Size & targetImageSize, InterpolationModes interpolationMode)
{
	float sx = (float)targetImageSize.getX() / (float)sourceImage.getWidth();
	float sy = (float)targetImageSize.getY() / (float)sourceImage.getHeight();

	return ImageTransformator::applyScaleAndCentralRotation(sourceImage, 0.0, targetImageSize,sx,sy, interpolationMode);
}
