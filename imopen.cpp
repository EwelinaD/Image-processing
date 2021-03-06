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

        for (int i = 0 ; i < sizeOfMask ; i++ )
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

    sizeOfMask = 2*rad+1;
    radius = rad;
//    cout <<"r="<<radius<<"::"<<rad<<endl;
//    cout <<"size="<<size<<endl;

    structure = new bool*[sizeOfMask];
    for (int i = 0 ; i < sizeOfMask ; i++ )
    {
        structure[i]= new bool[sizeOfMask];
    }

    for(int i = 0 ; i < rad+1; i++)
        for(int j = 0 ; j < rad+1; j++)
        {
            bool val=((rad-i)*(rad-i)+(rad-j)*(rad-j)<=rad*rad);
            structure[i][j]=val;
            structure[sizeOfMask-i-1][j]=val;
            structure[sizeOfMask-i-1][sizeOfMask-j-1]=val;
            structure[i][sizeOfMask-j-1]=val;
 //           cout <<"setting "<<i<<","<<j<<" to" <<(int) val<<endl;
        }
    //debug
    for(int i = 0 ; i < sizeOfMask; i++)
    {
        for(int j = 0 ; j < sizeOfMask; j++)
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

    for(int i = 0 ; i < sizeOfMask; i++)
        for(int j = 0 ; j < sizeOfMask; j++)
        {
            if(structure[i][j]==true)
                if (coordinatesInRange(i+posx-radius-1,j+posy-radius-1))
                {
                 //   cout << "A::"<<i+posx-radius-1<<"::"<<j+posy-radius-1<<"::"<<0;
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

    for(int i = 0 ; i < sizeOfMask; i++)
        for(int j = 0 ; j < sizeOfMask; j++)
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


int Imopen::findMinUnderMask()
{
    if( radius == 0 )
        return false;
    if( data == NULL)
        return false;

    minUnderMask=0xFFFFFFFF;

    for(int i = 0 ; i < sizeOfMask; i++)
        for(int j = 0 ; j < sizeOfMask; j++)
        {
            if( !coordinatesInRange(i+posx-radius,j+posy-radius) )
                continue;

                if(structure[i][j]==true)
                {
                    if(minUnderMask>data->pixel(i+posx-radius,j+posy-radius))
                    {
                        minUnderMask=data->pixel(i+posx-radius,j+posy-radius);
                    }
                }
        }
    return minUnderMask;
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

void Imopen::maximizeColorUnderMask(QRgb min_qrgb_int )
{
    if( radius == 0 )
        return;
    if( data == NULL)
        return;
    for(int i = 0 ; i < sizeOfMask; i++)
        for(int j = 0 ; j < sizeOfMask; j++)
        {
            if(structure[i][j]==true)
            {
                if (coordinatesInRange(i+posx-radius,j+posy-radius))
                {
                    if( data->pixel(i+posx-radius,j+posy-radius) < min_qrgb_int )
                    {
                        data->setPixel(i+posx-radius,j+posy-radius,min_qrgb_int);
                    }

                }
            }
        }
}

void Imopen::erode( QImage* tempImag)
{

    setData(opv->sourceImage);
//    tempImag->convertToFormat(QImage::Format_RGB888);
    for(int i=0; i < opv->sourceImage->width();i++)
        for(int j=0; j < opv->sourceImage->height();j++)
        {
            move(i,j);
            tempImag->setPixel(i,j,findMinUnderMask() );
        }
}


void Imopen::dilate( QImage* tempImag)
{
    setData( opv->pDestImag );
    for(int i=0; i < opv->pDestImag->width();i++)
        for(int j=0; j <  opv->pDestImag->height();j++)
        {
         /*   if(tempImag->pixel(i,j) == 0xFF000000)
            {
                paintItBlack();
            }
            */
            move(i,j);
            maximizeColorUnderMask(tempImag->pixel(i,j));
        }
}



void Imopen::openImage(int value )
{
    //reinitialize dest image
    if( opv->pDestImag != NULL)
        delete opv->pDestImag;
    QImage tempImag= QImage(*(opv->sourceImage));

    //create circular element and config it
    setRadius( value );
 //   setOptionsViewPtr(this);
    erode( &tempImag);

    //dilatation
    opv->pDestImag=new QImage(tempImag);
    dilate(&tempImag);

    //tideup n show
  //  imView->showDestImage(pDestImag);
}



void Imopen::setOptionsViewPtr(OptionsView* op)
{
    opv=op;
}
