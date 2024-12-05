#ifndef UTILITIES_H
#define UTILITIES_H

#include <SDL.h>

typedef struct {
    float x;
    float y;
    int renderX;
    int renderY;
} position;

static inline void UpdateRenderPosition(position* position) {
    position->renderX = (int)position->x;
    position->renderY = (int)position->y;
}

#endif // UTILITIES_H