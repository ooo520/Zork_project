#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include<QPushButton>
#include <QEvent>
#include <QKeyEvent>
#include <QColor>
#include <QPalette>
#include <QTextEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_south_clicked();
    void on_north_clicked();
    void on_east_clicked();
    void on_west_clicked();
    void on_enter_pressed( );

private:
    Ui::MainWindow *ui;
    QPushButton * push_button2;
    QPushButton * push_button_e;
    QPushButton * push_button_w;
    QPushButton * push_button_s;
    QPushButton * push_button_n;
};
#endif // MAINWINDOW_H

