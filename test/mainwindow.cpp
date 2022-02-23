#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->shell->setReadOnly(true);
    QColor c;
    QPalette pal = ui->shell->palette();
    pal.setColor(QPalette::Base, Qt::black);


    c.setRgb(0,0,0,255);
    ui->shell->setPalette(pal);
    ui->commande_shell->setPalette(pal);

    c.setRgb(255,255,255,255);
    ui->shell->setTextColor(c);ui->commande_shell->setTextColor(c);

    push_button2 = new QPushButton(this);
    push_button_w = new QPushButton(this);
    push_button_n = new QPushButton(this);
    push_button_s = new QPushButton(this);
    push_button_e = new QPushButton(this);

    int x,y,x2=this->frameGeometry().width(),
            y2=this->frameGeometry().height();

    push_button2->setText("Tap");
    push_button2->setGeometry(QRect(QPoint( x2/2 -(50/2) ,y2 -(50*2)-1 ), QSize(50, 50)));
    push_button2->geometry().getCoords(&x,&y,&x2,&y2);

    push_button_n->setText("North");
    push_button_n->setGeometry(QRect(QPoint(x,y+1 +(y2-y)), QSize(50, 50)));
    push_button_w->setText("West");
    push_button_w->setGeometry(QRect(QPoint(x-1 -(x2-x),y), QSize(50, 50)));
    push_button_e->setText("East");
    push_button_e->setGeometry(QRect(QPoint(x+1+ (x2-x),y), QSize(50, 50)));
    push_button_s->setText("South");
    push_button_s->setGeometry(QRect(QPoint(x,y-1 -(y2-y)), QSize(50, 50)));

    connect(push_button2, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(push_button_n, SIGNAL(clicked()), this, SLOT(on_north_clicked()));
    connect(push_button_w, SIGNAL(clicked()), this, SLOT(on_west_clicked()));
    connect(push_button_e, SIGNAL(clicked()), this, SLOT(on_east_clicked()));
    connect(push_button_s, SIGNAL(clicked()), this, SLOT(on_south_clicked()));
    connect(ui->shell,SIGNAL(keyPressEvent(QKeyEvent *e)),this,SLOT(new_command(QKeyEvent *e)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked(){
    ui->shell->setText("Hello\n");
    ui->shell->currentFont();
}
void MainWindow::on_south_clicked(){
    ui->shell->setText("go south\n");
    ui->shell->currentFont();
}
void MainWindow::on_north_clicked(){
    ui->shell->setText("go north\n");
    ui->shell->currentFont();
}
void MainWindow::on_east_clicked(){
    ui->shell->setText("go east\n");
    ui->shell->currentFont();
}
void MainWindow::on_west_clicked(){
    ui->shell->setText("go west\n");
    ui->shell->currentFont();
}
void MainWindow::new_command(QKeyEvent *e){
    if(e->key()){ui->shell->setText("new command" );}

    ui->commande_shell->clear();
}

/*
keyPressEvent(QKeyEvent *e)
*/
