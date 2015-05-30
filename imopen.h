#ifndef IMOPEN_H
#define IMOPEN_H
#include <QPixmap>
#include <QImage>
#include <iostream>


class Imopen
{
    int size;
    int radius;
    bool** structure;
    QImage* data;
    int posx,posy;
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

};

#endif // IMOPEN_H
