#include "kirschfilter.h"

using namespace std;


int KirschFilter::valueOfCurrentMask(int channel)
{
    int value=0;
    int x;
    for(int i=0; i<8; i++)
    {
        if(channel == 0)
            x = qRed(sourceColor[i]);
        if(channel == 1)
            x = qGreen(sourceColor[i]);
        if(channel == 2)
            x = qBlue(sourceColor[i]);

        value+=(mask[i]*x);
    }

    if(value<0){
        value=(-value);
    }
    return value;
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
    for(int i = 0 ; i < pKFsrcImage->width() ;i++ )
    {
        for(int j = 0 ; j < pKFsrcImage->height();j++ )
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

    int x0 = (imagX==0)?imagX:imagX-1;
    int x2 = (imagX==pKFsrcImage->width()-1)?imagX:imagX+1;
    int y0 = (imagY==0)?imagY:imagY-1;
    int y2 = (imagY==pKFsrcImage->height()-1)?imagY:imagY+1;


    sourceColor[0]=pKFsrcImage->pixel(x0,y0);
    sourceColor[1]=pKFsrcImage->pixel(x,y0);
    sourceColor[2]=pKFsrcImage->pixel(x2,y0);
    sourceColor[3]=pKFsrcImage->pixel(x2,y);
    sourceColor[4]=pKFsrcImage->pixel(x2,y2);
    sourceColor[5]=pKFsrcImage->pixel(x,y2);
    sourceColor[6]=pKFsrcImage->pixel(x0,y2);
    sourceColor[7]=pKFsrcImage->pixel(x0,y);
}

QRgb KirschFilter::getColorValue()
{
    int maxValue=0;
    int valueUnderMask;
int rt,gt,bt;
int rm =0;
int gm = 0;
int bm = 0;
    for(int i=0; i<8; i++)
    {
        rt=valueOfCurrentMask(0);
        if( rm < rt)
             rm = rt;
        gt=valueOfCurrentMask(1);
        if( gm < gt)
             gm = gt;
        bt=valueOfCurrentMask(2);
        if( bm < bt)
             bm = bt;

        nextMask();

  //      if(valueUnderMask>maxValue)
   //       maxValue=valueUnderMask;
    }
    if( bm > 0xff)
         bm = 0xff;
    if( gm > 0xff)
         gm = 0xff;
    if( rm > 0xff)
         rm = 0xff;

    maxValue=bm+0x100*gm+0x10000*rm;
    if(maxValue<0)
        maxValue=-maxValue;
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



