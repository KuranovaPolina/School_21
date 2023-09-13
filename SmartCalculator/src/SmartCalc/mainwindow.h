#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

extern "C" {
    #include "calculator.h"
    #include "credit.h"
}

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
    void add_math_opp();

    void add_digit();

    void add_func();

    void on_pushButton_AC_clicked();

    void on_pushButton_dot_clicked();

    void on_pushButton_left_br_clicked();

    void on_pushButton_right_br_clicked();

    void on_pushButton_x_clicked();

    void on_pushButton_del_last_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_graph_clicked();

    void on_pushButton_calculate_credit_clicked();

private:
    Ui::MainWindow *ui;
    void add_digit(QString digit);

    double xBegin, xEnd, h, X, yBegin, yEnd;
    int N;

    QVector<double> x, y;
};
#endif // MAINWINDOW_H
