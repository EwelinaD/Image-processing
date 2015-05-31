#include "geodistance.h"

using namespace std;
void GeoDistance::setImages(QImage *src, QImage **dest)
{
    srcIm=src;
    pdestIm=dest;

    initializeDistances(srcIm->width(),srcIm->height());

    srcW = srcIm->width();
    srcH= src->height();

}

int GeoDistance::normalizeDistValue(int l)
{
    if( l == -1)
        return 0;
    int ret;
    if( maxDist < 1 )
        return 0;
    ret = 255 - (255*l)/maxDist ;
    return ret;
}

bool GeoDistance::coordinatesInRange(int x, int y)
{
    if ((x >=0 )&& (x < srcIm->width() )
       && (y >=0 ) && (y < srcIm->height() ))
    {
        return true;
    }
    return false;
}


void GeoDistance::populate()
{
    QPoint qp = qpList.front();
    int x = qp.x();
    int y = qp.y();
    int nextDist = distances[x][y]+1;
    qpList.pop_front();

    if( mode == 1 )
    {
        checkAddNewPoint(x-1,y-1,nextDist);
        checkAddNewPoint(x+1,y-1,nextDist);
        checkAddNewPoint(x-1,y+1,nextDist);
        checkAddNewPoint(x+1,y+1,nextDist);
    }

    checkAddNewPoint(x,y-1,nextDist);

    checkAddNewPoint(x-1,y,nextDist);
    checkAddNewPoint(x+1,y,nextDist);

    checkAddNewPoint(x,y+1,nextDist);
}

void GeoDistance::initializeDistances(int w, int h)
{
    if( distances != NULL )
    {
        for( int i = 0 ; i < srcW ; i++)
        {
            delete[] distances[i];
        }
        delete[] distances;
    }

    distances = new int*[w];
    for( int i = 0 ; i < w ; i++)
    {
        distances[i] = new int[h];
        for (int j = 0 ; j < h ;j++)
        {
           distances[i][j] = -1;
        }
    }

}

void GeoDistance::checkAddNewPoint(int x, int y, int nextDist)
{
    if(coordinatesInRange(x,y))
    {
        if( distances[x][y] == -1 )
        {
            if( srcIm->pixel(x,y) == 0xFFFFFFFF )
            {
                cout << "Dodawanie QP:"<<x<<","<<y<<"   val:"<<nextDist<<"  prev:"<<distances[x,y]<<endl;
                distances[x][y] = nextDist;
                qpList.push_back(QPoint(x,y));
                maxDist = nextDist;
            }
        }
    }
}

void GeoDistance::processImage(int strtX, int strtY, int neighbourhood)
{
    if(srcIm==NULL)
        return;
    if(*pdestIm!=NULL)
    {
        delete *pdestIm;
    }

    *pdestIm = new QImage( srcIm->size(),QImage::Format_RGB32);
    startX =strtX;
    startY=strtY;
    mode = neighbourhood;


    maxDist = 0;

    distances[startX][startY] = 0;
    qpList.push_back(QPoint(strtX,strtY));
    while( !qpList.empty())
    {
        populate();
    }

    for(int i=0;i< srcH;i++)
    {
        for(int j=0;j< srcW;j++)
        {
            distances[i][j]=normalizeDistValue(distances[i][j]);
            (*pdestIm)->setPixel(i,j,distances[i][j]*0x010101);
        }
    }
/*
    for(int i=0;i< srcH;i++)
    {
        for(int j=0;j< srcW;j++)
        {
            printf("%5d",distances[j][i]);
        }
        cout<<endl;
    }
*/
}

GeoDistance::GeoDistance()
{
    distances = NULL;
    srcIm = NULL;
    pdestIm = NULL;


}

GeoDistance::~GeoDistance()
{
    if( distances != NULL )
    {
        for( int i = 0 ; i < srcW ; i++)
            delete[] distances[i];
    }
    delete[] distances;
}

