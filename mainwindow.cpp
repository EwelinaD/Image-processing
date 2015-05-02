#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->images->setOptView(ui->options);
    ui->options->setimView(ui->images);
}

MainWindow::~MainWindow()
{
    delete ui;
}
