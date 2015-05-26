#ifndef ELEM_MASK_H
#define ELEM_MASK_H
#include <QPixmap>
#include <QImage>
#include <iostream>


class elem_mask
{
    int size;
    int radius;
    bool** structure;
    QImage* data;
    int posx,posy;
    void deleteStructure();
    bool coordinatesInRange(int x, int y);
public:
    elem_mask();
    ~elem_mask();
    void move(int x, int y);
    void setData( QImage* qi);
    void setRadius(int rad);
    void paintItBlack();
    bool checkAnyWhitePixies();

};

#endif // ELEM_MASK_H
