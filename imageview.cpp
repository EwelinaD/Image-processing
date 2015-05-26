#include "imageview.h"
#include "ui_imageview.h"

ImageView::ImageView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
    srcScene=NULL;
    destScene=NULL;
    dstImage=NULL;
    srcImage=NULL;
}

ImageView::~ImageView()
{
    delete ui;

    if(srcScene!=NULL)
        delete srcScene;

    if(destScene!=NULL)
        delete destScene;

}

void ImageView::showSourceImage(QImage* im)
{
    srcImage = im;
    sourceImageMap = QPixmap::fromImage(*srcImage);

    if(srcScene!=NULL)
        delete srcScene;

    srcScene = new QGraphicsScene(this);
    srcScene->addPixmap(sourceImageMap);
    srcScene->setSceneRect(sourceImageMap.rect());
    ui->myImage->setScene(srcScene);
    ui->myImage->fitInView(srcScene->sceneRect(),Qt::KeepAspectRatio);
}

void ImageView::showDestImage(QImage *im)
{
    dstImage=im;
    destImageMap=QPixmap::fromImage(*dstImage);

    if(destScene!=NULL)
        delete destScene;

    destScene = new QGraphicsScene(this);
    destScene->addPixmap(destImageMap);
    destScene->setSceneRect(destImageMap.rect());
    ui->viewTransform->setScene(destScene);
    ui->viewTransform->fitInView(destScene->sceneRect(),Qt::KeepAspectRatio);

}

void ImageView::setOptView(OptionsView * optV)
{
    optView=optV;
}

