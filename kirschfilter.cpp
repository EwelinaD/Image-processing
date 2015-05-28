#include "kirschfilter.h"

using namespace std;


int KirschFilter::valueOfCurrentMask()
{
    int value=0;

    for(int i=0; i<8; i++)
    {
        value+=(mask[i]*sourceColor[i]);
    }

    if(value<0)
        value=(-value);
}

KirschFilter::KirschFilter()
{
    maskIndex=-1;
    nextMask();
}

KirschFilter::~KirschFilter()
{

}

void KirschFilter::nextMask()
{
    maskIndex=(maskIndex+1)%8;

    for(int i=0; i<3; i++)
    {
        mask[(i+maskIndex)%8]=5;
    }

    for(int i=0; i<5;i++)
    {
        mask[(i+maskIndex+3)%8]=-3;
    }

    /*
    for(int i=0; i<8; i++)
    {
        cout << mask[i] << " " <<endl;
    }
    */
}

void KirschFilter::moveMask(int imagX, int imagY)
{
    if(pKFsrcImage==NULL)
        return;

    x=imagX;
    y=imagY;

    sourceColor[0]=pKFsrcImage->pixel(imagX-1,imagY-1);
    sourceColor[1]=pKFsrcImage->pixel(imagX,imagY-1);
    sourceColor[2]=pKFsrcImage->pixel(imagX+1,imagY-1);
    sourceColor[3]=pKFsrcImage->pixel(imagX-1,imagY);
    sourceColor[4]=pKFsrcImage->pixel(imagX+1,imagY);
    sourceColor[5]=pKFsrcImage->pixel(imagX-1,imagY+1);
    sourceColor[6]=pKFsrcImage->pixel(imagX,imagY+1);
    sourceColor[7]=pKFsrcImage->pixel(imagX+1,imagY+1);
}

int KirschFilter::getMaximum()
{
    int maxValue;
    int tab[8];

    for(int i=0; i<8; i++)
    {
        tab[i]=valueOfCurrentMask();
        nextMask();
    }

    maxValue=tab[0];
    for(int i=1; i<8; i++)
    {
        if(tab[i]>maxValue)
            maxValue=tab[i];
    }
    return maxValue;

}

void KirschFilter::setKFdestImag(QImage *im)
{
    pKFdestImag=im;
}


void KirschFilter::setKFsrcImage(QImage *im)
{
    pKFsrcImage=im;
}



