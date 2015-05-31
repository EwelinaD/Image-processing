#include "nearest.h"

Nearest::Nearest()
{

}

Nearest::~Nearest()
{

}

void Nearest::setOpv(OptionsView *ov)
{
    opv=ov;
}

void Nearest::coordsNearest(int x, int y, int aa)
{
    double xs,ys,xss,yss;
    double alpha = -(double)(aa%90)*0.017454;
    double shiftX=0.5*(opv->sourceImage->width()*cos(alpha)+opv->sourceImage->height()*sin(alpha)-opv->sourceImage->width());

    double shiftY=0.5*(opv->sourceImage->width()*sin(alpha)+(1-cos(alpha))*opv->sourceImage->height());

    shiftX=x+shiftX;
    shiftY=y-shiftY;

    double r = sqrt(shiftX*shiftX+shiftY*shiftY);
    double beta = atan((double)shiftX/shiftY)-alpha;

    if(beta<0)
    {
        beta+=3.14;
    }

        xs = r*sin(beta);       //x coord of source image
        ys = r*cos(beta);

    switch(aa/90){
        case 0: xss = xs;
                yss = ys;
                break;
        case 1: xss = ys;
                yss = opv->sourceImage->width()-xs;
                break;
        case 2: xss = opv->sourceImage->width()-xs;
                yss = opv->sourceImage->height()-ys;
                break;
        case 3: yss = xs;
                xss = opv->sourceImage->height()-ys;
                break;
    }

    if(( xss > 0) && (xss < opv->sourceImage->width()) && (yss >0) && (yss <opv->sourceImage->height()))
    {
        int px = opv->sourceImage->pixel(xss,yss);
        opv->pDestImag->setPixel(x,y,px);
    }
}
