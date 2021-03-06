#ifndef OPTIONSVIEW_H
#define OPTIONSVIEW_H

#include <QWidget>
#include <QFileDialog>
#include <iostream>
#include <QString>
#include <QGroupBox>
#include <cmath>

#include "geodistance.h"
#include "imageview.h"
#include "imopen.h"

namespace Ui {
class OptionsView;

}
class Imopen;
class ImageView;

class OptionsView : public QWidget
{
    Q_OBJECT

public:
    QString imagePath;
    ImageView* imView;              //wskaznik na widget imageView
    QImage* sourceImage;            //wskaznik na wczytany z pliku obraz
    QImage* pDestImag;              //wskaźnik na koncowy obraz (poczatkowo jest to czarny prostokat)

public:
    explicit OptionsView(QWidget *parent = 0);
    void setimView(ImageView*);
    void createDestImage(int,int);
    void nearestInterpolation();
    void coordsNearest(int,int,int);
    void openImage();
    ~OptionsView();

//    void erode(Imopen* EM, QImage* tempImag);
    void dilate(Imopen* EM, QImage* tempImag);
private slots:
    void on_loadButton_clicked();
    void on_nearestButton_clicked(bool checked);
    void on_kirschButton_clicked(bool checked);
    void on_transformButton_clicked();
    void on_imopenButton_clicked(bool checked);
    void on_saveButton_clicked();

    void on_distanceButton_clicked(bool checked);

private:
    Ui::OptionsView *ui;

};

#endif // OPTIONSVIEW_H
