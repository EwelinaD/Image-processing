#ifndef GEODISTANCE_H
#define GEODISTANCE_H
#include <QImage>
#include <list>
#include <iostream>
#include <stdio.h>

using namespace std;

class GeoDistance
{

    QImage* srcIm;
    QImage** pdestIm;
    int srcW;
    int srcH;
    int maxDist;
    int mode;
    list<QPoint> qpList;
    int startX;
    int startY;
    int** distances;

public:
    void setImages(QImage* src, QImage **dest);
    int normalizeDistValue(int l);
    void populate();
    void initializeDistances(int w, int h);
    void checkAddNewPoint(int x, int y, int nextDist);
    bool coordinatesInRange(int x, int y);
    void processImage(int strtX, int strtY, int neighbourhood);
    GeoDistance();
    ~GeoDistance();
};

#endif // GEODISTANCE_H
