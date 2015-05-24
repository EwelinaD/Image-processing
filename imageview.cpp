#include "imageview.h"
#include "ui_imageview.h"

ImageView::ImageView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
    scene=NULL;
    transformScene=NULL;
}

ImageView::~ImageView()
{
    delete ui;
    //delete imageObject;

    if(scene!=NULL)
        delete scene;

    if(transformScene!=NULL)
        delete transformScene;
}

void ImageView::showImage(QImage* im)
{
    //imageObject = new QImage(optView->imagePath,0);
    imageObject = im;
    image = QPixmap::fromImage(*imageObject);

    if(scene!=NULL)
        delete scene;

    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->myImage->setScene(scene);

    ui->myImage->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);

}

void ImageView::showTransform(QImage *im)
{
    transformObject=im;
    transformImage=QPixmap::fromImage(*transformObject);

    if(transformScene!=NULL)
        delete transformScene;

    transformScene = new QGraphicsScene(this);
    transformScene->addPixmap(transformImage);
    transformScene->setSceneRect(transformImage.rect());
    ui->viewTransform->setScene(transformScene);
    ui->viewTransform->fitInView(transformScene->sceneRect(),Qt::KeepAspectRatio);

}

void ImageView::setOptView(OptionsView * optV)
{
    optView=optV;
}

