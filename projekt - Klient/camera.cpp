#include "camera.h"

CCamera::CCamera()
{
    x = y = zoom = 0;
}

CCamera::~CCamera()
{
}

void CCamera::setPos(float i, float j) {
    x = i;
    y = j;
}

void CCamera::setStart(float i, float j) {
    startX = i;
    startY = j;
}

void CCamera::addPos(float i, float j) {
    x += i;
    y += j;
}

void CCamera::setZoom(float i) {
    zoom = i;
    // TODO
}

void CCamera::update() {
    al_identity_transform(&coord);
    al_translate_transform(&coord, -x + startX, -y + startY);
    al_use_transform(&coord);
}

void CCamera::reset() {
    ALLEGRO_TRANSFORM current = coord;
    al_translate_transform(&current, x - startX, y - startY);
    al_use_transform(&current);
}
