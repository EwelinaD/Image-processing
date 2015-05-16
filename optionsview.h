#ifndef OPTIONSVIEW_H
#define OPTIONSVIEW_H

#include <QWidget>
#include <QFileDialog>
#include <iostream>
#include <QString>

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
    ~OptionsView();


private slots:
    void on_loadButton_clicked();

    void on_nearestButton_clicked(bool checked);

private:
    Ui::OptionsView *ui;
    ImageView* imView;

};

#endif // OPTIONSVIEW_H
