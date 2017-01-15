#include "AlternativeBlender.h"


void AlternativeBlender::BlendOnImage(Image screen, std::vector<Blendable> blendables)
{
	uint32_t * screenPixmap = (uint32_t * )screen.getPixmap();
	unsigned bgHeight = screen.getHeight();
	unsigned bgWidth = screen.getWidth();

	for (unsigned i = 0; i < blendables.size(); i++) {
		uint32_t * blendedPixmap = (uint32_t *) blendables.at(i).image.getPixmap();
		unsigned blendedWidth = blendables.at(i).image.getWidth();
		unsigned blendedHeight = blendables.at(i).image.getHeight();
		int tx = blendables.at(i).centerX - blendedWidth / 2;
		int ty = blendables.at(i).centerY - blendedHeight / 2;

		for (int row = 0; row < blendedHeight; row++) {
			for (int column = 0; column < blendedWidth; column++) {
				if (tx + column < 0) {
					continue;
				}
				else if(ty+row <0){
					continue;
				}
				else if (tx + column >= bgWidth) {
					break;
				}
				else if(ty+ row >= bgHeight)
				{
					// terminate 
					row = 65000;
					break;
				}


				// cast for access single colour element
				uint8_t * color = (uint8_t *) &(blendedPixmap[row*blendedWidth + column]);
				uint8_t * bgColor = (uint8_t *)&(screenPixmap[(row + ty)*bgWidth + column+tx]);

				float alpha = (float)color[3];
				alpha = alpha/255.0;
				
				bgColor[0] = ((float)color[0])*alpha + ((float)bgColor[0])*(1.0 - alpha);
				bgColor[1] = ((float)color[1])*alpha + ((float)bgColor[1])*(1.0 - alpha);
				bgColor[2] = ((float)color[2])*alpha + ((float)bgColor[2])*(1.0 - alpha);
			}
		}
	}
}
