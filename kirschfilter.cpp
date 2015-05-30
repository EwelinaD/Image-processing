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
    pKFsrcImage = NULL;
    pKFdestImag = NULL;
    maskIndex=-1;
    nextMask();
}

void KirschFilter::executeKirchOnWholeImage()
{

    if( pKFsrcImage == NULL)
        return;

    if( pKFdestImag == NULL)
        return;

    if( *pKFdestImag != NULL)
        delete *pKFdestImag;

    *pKFdestImag = new QImage(pKFsrcImage->size(),QImage::Format_RGB32);

    QRgb countedValue;
    for(int i = 1 ; i < pKFsrcImage->width()-1 ;i++ )
    {
        for(int j = 1 ; j < pKFsrcImage->height()-1 ;j++ )
        {
            moveMask(i,j);
            countedValue = getColorValue();
            (*pKFdestImag)->setPixel(i,j,countedValue);
        }
    }
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

QRgb KirschFilter::getColorValue()
{
    int maxValue=0;
    int valueUnderMask;

    for(int i=0; i<8; i++)
    {
        valueUnderMask=valueOfCurrentMask();
        nextMask();
        if(valueUnderMask>maxValue)
            maxValue=valueUnderMask;
    }

    return maxValue;

}

void KirschFilter::setKFdestImag(QImage **im)
{
    pKFdestImag=im;
}


void KirschFilter::setKFsrcImage(QImage *im)
{
    pKFsrcImage=im;
}



