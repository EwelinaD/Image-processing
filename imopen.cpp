#include "imopen.h"
using namespace std;

Imopen::Imopen()
{
    structure=NULL;
    data=NULL;
    radius = 0;
    posx = 0;
    posy = 0;
}

Imopen::~Imopen()
{
    deleteStructure();
}

void Imopen::move(int x, int y)
{
    posx = x;
    posy = y;
}

void Imopen::deleteStructure()
{
    if (structure!=NULL)
    {

        for (int i = 0 ; i < size ; i++ )
        {
            delete[] structure[i];
            structure[i] = NULL;
        }
        delete[] structure;
        structure = NULL;
    }
}

void Imopen::setData(QImage *qi)
{
    data = qi;
}

void Imopen::setRadius(int rad)
{
//    cout <<"r="<<radius<<"::"<<rad<<endl;
    if( rad < 1 )
        return;
    deleteStructure();

    size = 2*rad+1;
    radius = rad;
//    cout <<"r="<<radius<<"::"<<rad<<endl;
//    cout <<"size="<<size<<endl;

    structure = new bool*[size];
    for (int i = 0 ; i < size ; i++ )
    {
        structure[i]= new bool[size];
    }

    for(int i = 0 ; i < rad+1; i++)
        for(int j = 0 ; j < rad+1; j++)
        {
            bool val=((rad-i)*(rad-i)+(rad-j)*(rad-j)<=rad*rad);
            structure[i][j]=val;
            structure[size-i-1][j]=val;
            structure[size-i-1][size-j-1]=val;
            structure[i][size-j-1]=val;
 //           cout <<"setting "<<i<<","<<j<<" to" <<(int) val<<endl;
        }
    //debug
    for(int i = 0 ; i < size; i++)
    {
        for(int j = 0 ; j < size; j++)
        {
            if (structure[i][j])
                cout<<"#";
            else
                cout <<" ";
        }
        cout <<endl;
    }
}

void Imopen::paintItBlack()
{
    if( radius == 0 )
        return;
    if( data == NULL)
        return;

    for(int i = 0 ; i < size; i++)
        for(int j = 0 ; j < size; j++)
        {
            if(structure[i][j]==true)
                if (coordinatesInRange(i+posx-radius-1,j+posy-radius-1))
                {
                     data->setPixel(i+posx-radius-1,j+posy-radius-1,0);
                }
        }
}

bool Imopen::checkAnyWhitePixies()
{

    if( radius == 0 )
        return false;
    if( data == NULL)
        return false;

    for(int i = 0 ; i < size; i++)
        for(int j = 0 ; j < size; j++)
        {
            if( !coordinatesInRange(i+posx-radius-1,j+posy-radius-1) )
                continue;
     //       cout <<"val"<<i<<","<<j<<":"<<data->pixel(i+posx-radius-1,j+posy-radius-1)<<endl;
            if(structure[i][j]==true)
                if( data->pixel(i+posx-radius-1,j+posy-radius-1) == 0xFFFFFFFF)
                {
   //                 cout <<"white occured on"<<i+posx-radius-1<<","<<j+posy-radius-1 <<endl;
                    return true;
                }
        }
    return false;
}

bool Imopen::coordinatesInRange(int x, int y)
{
    if ((x >0 )&& (x < data->width() )
       && (y >0 ) && (y < data->height() ))
    {
        return true;
    }
    return false;
}

void Imopen::erode( QImage* tempImag)
{
    setData(opv->sourceImage);
    for(int i=0; i < opv->sourceImage->width();i++)
        for(int j=0; j < opv->sourceImage->height();j++)
        {
            move(i,j);
            if( checkAnyWhitePixies() )
            {
                tempImag->setPixel(i,j,0xFF000000);
            }
        }
}


void Imopen::dilate( QImage* tempImag)
{
    setData( opv->pDestImag );
    for(int i=0; i < opv->pDestImag->width();i++)
        for(int j=0; j <  opv->pDestImag->height();j++)
        {
            if(tempImag->pixel(i,j) == 0xFFFFFFFF)
            {
                move(i,j);
                paintItBlack();
            }
        }
}



void Imopen::setOptionsViewPtr(OptionsView* op)
{
    opv=op;
}
