#ifndef OPTIONSVIEW_H
#define OPTIONSVIEW_H

#include <QWidget>
#include <QFileDialog>
#include <iostream>
#include <QString>
#include <QGroupBox>

#include "imageview.h"

namespace Ui {
class OptionsView;

}

class ImageView;

class OptionsView : public QWidget
{
    Q_OBJECT

public:
    QString imagePath;

public:
    explicit OptionsView(QWidget *parent = 0);
    void setimView(ImageView*);
    void createBlackImage(int,int);
    ~OptionsView();

private slots:
    void on_loadButton_clicked();
    void on_nearestButton_clicked(bool checked);
    void on_kirschButton_clicked(bool checked);
    void on_transformButton_clicked();
    void on_imopenButton_clicked(bool checked);

private:
    Ui::OptionsView *ui;
    ImageView* imView;
    QImage* imageObject;    //wskaznik na wczytany z pliku obraz
    QImage* qim;        //wskaźnik na czarny kwadrat

};

#endif // OPTIONSVIEW_H
