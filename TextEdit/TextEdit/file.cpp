#include "file.h"
#include "ui_file.h"
#include <QPushButton>

File::File(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);
   //connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(okClicked));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &File::okClicked);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel),&QPushButton::clicked,this,&File::close);
}


void File::okClicked(){
    emit filePath(ui->lineEdit->text());
    close();
}
File::~File()
{
    delete ui;
}
