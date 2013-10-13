#ifndef EXOBJECT_H_INCLUDED
#define EXOBJECT_H_INCLUDED

class CMain
{
    public:

    float x,y, w,h;

    virtual float getX() { return x; }
    virtual float getY() { return y; }
    virtual void  setX(float x) { this->x = x; }
    virtual void  setY(float y) { this->y = y; }

    virtual float getW() { return w; }
    virtual float getH() { return h; }
    virtual void  setW(float w) { this->w = w; }
    virtual void  setH(float h) { this->h = h; }

    virtual void addX(float x) { this->x += x; }
    virtual void addY(float y) { this->y += y; }
    virtual void addW(float w) { this->w += w; }
    virtual void addH(float h) { this->h += h; }

    CMain()
    {
        x = y = w = h = 0;
    }

};


#endif // EXOBJECT_H_INCLUDED
