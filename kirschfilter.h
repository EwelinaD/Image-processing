#ifndef KIRSCHFILTER_H
#define KIRSCHFILTER_H

#include <QImage>
#include <QRgb>

#include <iostream>

class KirschFilter
{

private:
    QImage* pKFsrcImage;         //wskaznik na obraz zrodlowy
    QImage** pKFdestImag;
    int mask[8];
    int x;
    int y;
    int maskIndex;
    QRgb sourceColor[8];        //odpowiadaja pikselom w masce


    int valueOfCurrentMask();       //wylicza wartosc aktualnej maski


public:
    KirschFilter();
    void executeKirchOnWholeImage();
    void setKFsrcImage(QImage* im);
    void nextMask();            //tworzy nowa maske
    void moveMask(int imagX, int imagY);
    QRgb getColorValue();       //zwraca kolor z operatora Kirscha
    void setKFdestImag(QImage** im);
    int maxColorByChannels(int a, int b);
    ~KirschFilter();
};

#endif // KIRSCHFILTER_H
