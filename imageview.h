#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPixmap>
#include <QImage>

#include "optionsview.h"

namespace Ui {
class ImageView;
}

class OptionsView;

class ImageView : public QWidget
{
    Q_OBJECT
public:
     QImage *dstImage;

public:
    explicit ImageView(QWidget *parent = 0);
    void showSourceImage(QImage*);
    void showDestImage(QImage*);
    void setOptView(OptionsView*);
    ~ImageView();

private:
        Ui::ImageView *ui;
        QPixmap sourceImageMap;           //pixmapa na zrodlowy obraz
        QPixmap destImageMap;             //pixmapa na koncowy obraz
        QImage  *srcImage;
        QGraphicsScene *srcScene;
        QGraphicsScene *destScene;
        OptionsView* optView;               //wskaznik na widget optionsView
};

#endif // IMAGEVIEW_H
