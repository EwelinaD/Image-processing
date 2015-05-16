#include "optionsview.h"
#include "ui_optionsview.h"

using namespace std;

OptionsView::OptionsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsView)
{
    ui->setupUi(this);
    ui->angleEdit->setDisabled(true);
}

OptionsView::~OptionsView()
{
    delete ui;
}

void OptionsView::setimView(ImageView * im)
{
    imView=im;
}

void OptionsView::on_loadButton_clicked()
{
    imagePath = QFileDialog::getOpenFileName(
                this, tr("Open File"),"",tr("Images (*.png *.xpm *.jpg *.jpeg *.bmp *.tif"));
    imView->showImage();

}

void OptionsView::on_nearestButton_clicked(bool checked)
{
    if(checked)
    {
        ui->angleEdit->setEnabled(true);
    }
    else
    {
        ui->angleEdit->setDisabled(false);
    }
}
