#include "optionsview.h"
#include "ui_optionsview.h"
#include "imopen.h"
#include "kirschfilter.h"

using namespace std;

OptionsView::OptionsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsView)
{
    ui->setupUi(this);
    sourceImage=NULL;
    pDestImag=NULL;
    imView=NULL;

    ui->angleSpinBox->setDisabled(true);
    ui->sizeSpinBox->setDisabled(true);
    ui->nearestButton->setCheckable(false);
    ui->kirschButton->setCheckable(false);
    ui->imopenButton->setCheckable(false);
}

OptionsView::~OptionsView()
{
    delete ui;
    if(sourceImage!=NULL)
        delete sourceImage;

    if(pDestImag!=NULL)
        delete pDestImag;
}

void OptionsView::setimView(ImageView * im)
{
    imView=im;
}

void OptionsView::createDestImage(int w, int h)
{
    if(pDestImag!=NULL)
        delete pDestImag;

    pDestImag = new QImage(w,h,QImage::Format_RGB32);
    pDestImag->fill(0);
}

void OptionsView::on_loadButton_clicked()
{
    imagePath = QFileDialog::getOpenFileName(this);

    if(sourceImage!=NULL)
        delete sourceImage;

 //   sourceImage = new QImage(imagePath,0);
//    sourceImage->convertToFormat(QImage::Format_RGB32);
    sourceImage = new QImage();
    sourceImage->load(imagePath,0);

    imView->showSourceImage(sourceImage);
    ui->nearestButton->setCheckable(true);
    ui->imopenButton->setCheckable(true);
    ui->kirschButton->setCheckable(true);

}

void OptionsView::on_nearestButton_clicked(bool checked)
{
    if(sourceImage==NULL)
        return;

    else
    {
        ui->nearestButton->setCheckable(true);
        ui->angleSpinBox->setEnabled(checked);
    }

}

void OptionsView::on_kirschButton_clicked(bool checked)
{
    if(sourceImage==NULL)
        return;

    else
    {
        ui->kirschButton->setCheckable(true);
    }
}


void OptionsView::on_imopenButton_clicked(bool checked)
{
    if(sourceImage==NULL)
        return;

    else
    {
        ui->imopenButton->setCheckable(true);
        ui->sizeSpinBox->setEnabled(checked);
    }
}

void OptionsView::coordsNearest(int x, int y, int aa)
{
    double xs,ys;

    double alpha = -(double)aa*0.017454;
    double shiftX=0.5*(sourceImage->width()*cos(alpha)+sourceImage->height()*sin(alpha)-sourceImage->width());
  //  double shiftY=0.5*(sourceImage->width()*sin(alpha)+sourceImage->height()*cos(alpha)-sourceImage->height());
//    double shiftY=sourceImage->width()*sin(alpha);
    double shiftY=0.5*(sourceImage->width()*sin(alpha)+(1-cos(alpha))*sourceImage->height());

    shiftX=x+shiftX;
   shiftY=y-shiftY;


    double r = sqrt(shiftX*shiftX+shiftY*shiftY);
    double beta = atan((double)shiftX/shiftY)-alpha;



    if(beta<0)
    {
        beta+=3.14;
    }

        xs = r*sin(beta);       //x coord of source image
        ys = r*cos(beta);



    if(( xs > 0) && (xs < sourceImage->width()) && (ys >0) && (ys <sourceImage->height()))
    {
        int px = sourceImage->pixel(xs,ys);
        pDestImag->setPixel(x,y,px);
    }
}

void OptionsView::nearestInterpolation()
{
    int alpha = ui->angleSpinBox->value();

       for(int x=0; x<pDestImag->width(); x++)
       {
           for(int y=0; y<pDestImag->height(); y++)
           {
               coordsNearest(x,y,alpha);
           }
       }
}

void OptionsView::on_transformButton_clicked()
{
    if(ui->nearestButton->isChecked())
    {
        createDestImage(sourceImage->width(),sourceImage->height());
        nearestInterpolation();
        imView->showDestImage(pDestImag);
    }

    if (ui->kirschButton->isChecked())
    {
        KirschFilter kf;
        kf.setKFsrcImage(sourceImage);
        kf.setKFdestImag(&pDestImag);
        kf.executeKirchOnWholeImage();
        imView->showDestImage(pDestImag);


    }

    if(ui->imopenButton->isChecked())
    {
        Imopen EM;
        EM.setOptionsViewPtr(this);
        EM.openImage(ui->sizeSpinBox->value());
        imView->showDestImage(pDestImag);
    }
}

void OptionsView::on_saveButton_clicked()
{
    QString imagePath = QFileDialog::getSaveFileName(this);
    pDestImag->save(imagePath);
}
