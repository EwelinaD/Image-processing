#include "optionsview.h"
#include "ui_optionsview.h"

using namespace std;

OptionsView::OptionsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsView)
{
    ui->setupUi(this);
    ui->angleEdit->setDisabled(true);
    ui->sizeEdit->setDisabled(true);
    imageObject=NULL;
    ui->nearestButton->setCheckable(false);
    ui->kirschButton->setCheckable(false);
    ui->imopenButton->setCheckable(false);
}

OptionsView::~OptionsView()
{
    delete ui;
    if(imageObject!=NULL)
        delete imageObject;
}

void OptionsView::setimView(ImageView * im)
{
    imView=im;
}

void OptionsView::on_loadButton_clicked()
{
    imagePath = QFileDialog::getOpenFileName(
                this, tr("Open File"),"",tr("Images (*.png *.xpm *.jpg *.jpeg *.bmp *.tif"));

    if(imageObject!=NULL)
        delete imageObject;

    imageObject = new QImage(imagePath,0);
    //imageObject->convertToFormat(QImage::Format_RGB32);
    imView->showImage(imageObject);
    ui->nearestButton->setCheckable(true);

}

void OptionsView::on_nearestButton_clicked(bool checked)
{
    if(imageObject==NULL)
        return;

    else
    {
        ui->nearestButton->setCheckable(true);
        ui->angleEdit->setEnabled(checked);
    }

}

void OptionsView::on_kirschButton_clicked(bool checked)
{
    if(imageObject==NULL)
    {
        return;
    }
    else
    {
        ui->kirschButton->setCheckable(true);
    }
}


void OptionsView::on_imopenButton_clicked(bool checked)
{
    if(imageObject==NULL)
    {
        return;
    }
    else
    {
        ui->imopenButton->setCheckable(true);
        ui->sizeEdit->setEnabled(checked);
    }
}

void OptionsView::on_transformButton_clicked()
{
    if(ui->nearestButton->isChecked())
    {
        cout << "nearest" << endl;
    }

    if (ui->kirschButton->isChecked())
    {
        cout << "Kirsch" << endl;
    }

    if(ui->imopenButton->isChecked())
    {
        cout << "imopen" << endl;
    }
}
