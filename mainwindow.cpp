#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Viewer.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(new Viewer);
}

MainWindow::~MainWindow()
{
    delete ui;
}
