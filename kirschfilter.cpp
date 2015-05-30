#include "kirschfilter.h"

using namespace std;


int KirschFilter::valueOfCurrentMask()
{
    int value=0;

    for(int i=0; i<8; i++)
    {
        value+=(mask[i]*sourceColor[i]);
    }

    if(value<0){
       // cout <<"A::"<<value<<endl;
        value=(-value);
    }
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

    for(int i=0; i<8; i++)
    {
        valueUnderMask=valueOfCurrentMask();
        nextMask();
      //  maxValue = maxColorByChannels(valueUnderMask,maxValue);
/*
        if ( (valueUnderMask & 0x00ff0000) >  (maxValue & 0x00ff0000) )
        {
           maxValue &= 0x0000FFFF;
           maxValue += valueUnderMask & 0x00ff0000 ;
        }
        if ( (valueUnderMask & 0x0000ff00) >  (maxValue & 0x0000ff00) )
        {
            maxValue &= 0x00FF00FF;
            maxValue += valueUnderMask & 0x0000ff00 ;
        }
        if ( (valueUnderMask & 0x000000ff) >  (maxValue & 0x000000ff) )
        {
            maxValue &= 0x00FFFF00;
            maxValue += valueUnderMask & 0x000000ff ;
        }
        maxValue = valueUnderMask ^0xffffffff ;*/
        if(valueUnderMask>maxValue)
            maxValue=valueUnderMask;
    }
    if(maxValue<0)
        maxValue=-maxValue;
    return maxValue;

}

void KirschFilter::setKFdestImag(QImage **im)
{
    pKFdestImag=im;
}

int KirschFilter::maxColorByChannels(int aa, int bb)
{
    int r,g,b;
   // QRgb aa = QRbg(aaa);
 //   QRgb bb = QRbg(bbb);
    QRgb maxed;

    if ( (aa & 0x00ff0000) >  (bb & 0x00ff0000) )
        r = aa & 0x00ff0000 ;
    else
        r = bb & 0x00ff0000 ;

    if ( (aa & 0x0000ff00 )>  (bb & 0x0000ff00 ))
        g = aa & 0x0000ff00;
    else
        g =  bb & 0x0000ff00;


    if ( (aa & 0x000000ff )>  (bb & 0x000000ff) )
       b=  aa & 0x000000ff;
    else
        b= bb & 0x000000ff;


    return 0xffffffff - r-g-b;
}


void KirschFilter::setKFsrcImage(QImage *im)
{
    pKFsrcImage=im;
}



