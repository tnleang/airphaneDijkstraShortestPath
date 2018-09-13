#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWebChannel>
#include <QWebEngineView>
#include <QFile>
#include <QMainWindow>
#include <iostream>
#include <cmath>

#include "run.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Q_INVOKABLE void Update(const QString &airportName);



private slots:
    void on_compute_clicked();

private:
    Ui::MainWindow *ui;
    QWebEngineView* view;
    QWebEnginePage* page;
    QWebChannel* channel;
    void setUpWebEnginer();

    Run r;
    bool source;
};

#endif // MAINWINDOW_H
