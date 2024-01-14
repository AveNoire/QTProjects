#include "finddialog.h"
#include <QtWidgets>

FindDialog::FindDialog(QWidget *parent): QDialog(parent){
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    caseCheckbox = new QCheckBox(tr("Match &case"));
    backwardCheckbox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("&Close"));

    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableFindButton(QString)));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckbox);
    leftLayout->addWidget(backwardCheckbox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle("Find");
    setFixedHeight(sizeHint().height());
}
void FindDialog::findClicked(){
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckbox->isChecked() ? Qt::CaseSensitive: Qt::CaseInsensitive;
    if(backwardCheckbox->isChecked()){
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void FindDialog::enableFindButton(const QString &text){
    findButton->setEnabled(!text.isEmpty());
}