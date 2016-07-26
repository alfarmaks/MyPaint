#include "about.h"
#include "ui_about.h"
#include <QPixmap>
#include <QPalette>
#include <QSize>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    //set image
    QPixmap image(":/ToImages/Images/For_about.png");
    ui->Picture->setPixmap(image);

    // set black background
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::darkMagenta);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->setModal(true);

    //set color of labels text
    ui->label->setStyleSheet("color:white");
    ui->label_2->setStyleSheet("color:white");
    ui->label_3->setStyleSheet("color:white");

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(close()));

}

About::~About()
{
    delete ui;
}
