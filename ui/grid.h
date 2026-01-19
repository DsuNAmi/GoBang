#ifndef __GRID_H__
#define __GRID_H__

#include "revar.h"

/* macro */
#define GRID_SIZE_WIDTH    15
#define GRID_SIZE_HEIGHT   15
#define GRID_POINTS_NUM   (GRID_SIZE_WIDTH * GRID_SIZE_HEIGHT)



typedef struct tagUiPoint
{
    INT ix;
    INT iy;
}UI_POINT_S;


typedef struct tagUiGrid
{
    ULONG ulWidth;
    ULONG ulHeight;

}UI_GRID_S;

#endif // __GRID_H__