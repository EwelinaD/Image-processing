#ifndef IMOPEN_H
#define IMOPEN_H
#include <QPixmap>
#include <QImage>
#include <iostream>
#include "optionsview.h"

class OptionsView;
class Imopen
{
    int size;
    int radius;
    bool** structure;
    QImage* data;
    int posx,posy;
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

};

#endif // IMOPEN_H
