#include "imageview.h"
#include "ui_imageview.h"

ImageView::ImageView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
}

ImageView::~ImageView()
{
    delete ui;
    delete imageObject;
}

void ImageView::showImage()
{
    imageObject = new QImage();
    imageObject->load(optView->imagePath);
    image = QPixmap::fromImage(*imageObject);
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->myImage->setScene(scene);

}

void ImageView::setOptView(OptionsView * optV)
{
    optView=optV;
}
