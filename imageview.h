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
    explicit ImageView(QWidget *parent = 0);
    void showImage(QImage*);
    void showTransform(QImage*);
    void setOptView(OptionsView*);
    ~ImageView();

private:
        Ui::ImageView *ui;
        QPixmap image;
        QPixmap transformImage;
        QImage  *imageObject;
        QImage *transformObject;
        QGraphicsScene *scene;
        QGraphicsScene *transformScene;
        OptionsView* optView;
};

#endif // IMAGEVIEW_H
