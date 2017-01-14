#pragma once

# define M_PI           3.14159265358979323846  /* pi */

// [x,y)
#define IN_RANGE(x,from,to) (x>=from && x<to)?true:false
#define IN_2D_RANGE(x,y,xFrom,xTo,yFrom,yTo) ( IN_RANGE(x,xFrom,xTo) && IN_RANGE(y,yFrom,yTo))?true:false
