#include "mainwindow.h"
#include "file.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    ui->statusbar->showMessage("OK");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_File_triggered()
{
    File *wnd = new File(this);
    wnd->show();
    connect(wnd, SIGNAL(filePath(QString)), this, SLOT(openFile(QString)));
}


void MainWindow::on_actionSave_File_triggered()
{
    File *wnd = new File(this);
    wnd->show();
    connect(wnd, SIGNAL(filePath(QString)), this, SLOT(saveFile(QString)));
}

void MainWindow::openFile(const QString &filePath)
{
    QFile mFile(filePath);
    if(!mFile.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::information(this, "Error", "Error open file");
        ui->statusbar->showMessage("Error open file:" + filePath);
        return;
    }
    QTextStream stream(&mFile);
    QString buffer = stream.readAll();
    ui->textEdit->setText(buffer);
    ui->statusbar->showMessage("Read to file");
    mFile.flush();
    mFile.close();
}

void MainWindow::saveFile(const QString &filePath)
{
    QFile mFile(filePath);
    if(!mFile.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::information(this, "Error", "Error save file");
        ui->statusbar->showMessage("Error save file");
        return;
    }
    QTextStream stream(&mFile);
    stream << ui->textEdit->toPlainText();
    ui->statusbar->showMessage("Write to file:" + filePath);
    mFile.close();
}
