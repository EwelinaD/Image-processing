#ifndef IMOPEN_H
#define IMOPEN_H
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QRgb>
#include "optionsview.h"

class OptionsView;
class Imopen
{
    int sizeOfMask;
    int radius;
    bool** structure;
    QImage* data;
    int posx,posy;
    int minUnderMask;
    OptionsView* opv;
    void deleteStructure();
    bool coordinatesInRange(int x, int y);
public:
    Imopen();
    ~Imopen();
    void move(int x, int y);
    void setData( QImage* qi);
    void setRadius(int rad);
    void paintItBlack();
    bool checkAnyWhitePixies();
    void setOptionsViewPtr(OptionsView* op);
    void erode( QImage* tempImag);

    void dilate(QImage *tempImag);
    void openImage(int value);
    int findMinUnderMask();
};

#endif // IMOPEN_H
