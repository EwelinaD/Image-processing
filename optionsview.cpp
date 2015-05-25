#include "optionsview.h"
#include "ui_optionsview.h"

using namespace std;

OptionsView::OptionsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsView)
{
    ui->setupUi(this);
    imageObject=NULL;
    pBlackImag=NULL;
    imView=NULL;

    ui->angleSpinBox->setDisabled(true);
    ui->sizeEdit->setDisabled(true);
    ui->nearestButton->setCheckable(false);
    ui->kirschButton->setCheckable(false);
    ui->imopenButton->setCheckable(false);
}

OptionsView::~OptionsView()
{
    delete ui;
    if(imageObject!=NULL)
        delete imageObject;

    if(pBlackImag!=NULL)
        delete pBlackImag;
}

void OptionsView::setimView(ImageView * im)
{
    imView=im;
}

void OptionsView::createBlackImage(int w, int h)
{
    if(pBlackImag!=NULL)
        delete pBlackImag;

    pBlackImag = new QImage(w,h,QImage::Format_RGB32);
    pBlackImag->fill(0);
}

void OptionsView::on_loadButton_clicked()
{
    imagePath = QFileDialog::getOpenFileName(
                this, tr("Open File"),"",tr("Images (*.png *.xpm *.jpg *.jpeg *.bmp *.tif"));

    if(imageObject!=NULL)
        delete imageObject;

    imageObject = new QImage(imagePath,0);
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
        ui->angleSpinBox->setEnabled(checked);
    }

}

void OptionsView::on_kirschButton_clicked(bool checked)
{
    if(imageObject==NULL)
        return;

    else
    {
        ui->kirschButton->setCheckable(true);
    }
}


void OptionsView::on_imopenButton_clicked(bool checked)
{
    if(imageObject==NULL)
        return;

    else
    {
        ui->imopenButton->setCheckable(true);
        ui->sizeEdit->setEnabled(checked);
    }
}

void OptionsView::coordsNearest(int x, int y, int aa)
{
    double alpha = (double)aa*0.017454;
    double r = sqrt(x*x+y*y);
    double beta = atan((double)x/y)-alpha;

    double xs = r*sin(beta);       //x coord of source image
    double ys = r*cos(beta);

    if(( xs > 0) && (xs < imageObject->width()) && (ys >0) && (ys <imageObject->height())){
    int px = imageObject->pixel(xs,ys);
    pBlackImag->setPixel(x,y,px);
    }
}

void OptionsView::nearestInterpolation()
{
    int alpha = ui->angleSpinBox->value();
    cout << alpha << endl;
 /*   for(int x=(pBlackImag->width()/(-2)); x<(pBlackImag->width()/2); x++)
    {
        for(int y=(pBlackImag->height()/(-2)); y<(pBlackImag->height()/2); y++)
        {
            coordsNearest(x,y,alpha);
        }
    }*/

       for(int x=0; x<pBlackImag->width(); x++)
       {
           for(int y=0; y<pBlackImag->height(); y++)
           {
               coordsNearest(x,y,alpha);
           }
       }
}

void OptionsView::on_transformButton_clicked()
{
    if(ui->nearestButton->isChecked())
    {
        cout << "nearest" << endl;

        createBlackImage(imageObject->width(),imageObject->height());
        nearestInterpolation();
        imView->showTransform(pBlackImag);
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

void OptionsView::on_saveButton_clicked()
{

}
