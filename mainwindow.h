#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "queryImpl.h"

#include <QMainWindow>

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
    void    execute();

private:
    Ui::MainWindow* ui;
    CQueryImpl*     m_pQueryImpl;

};
#endif // MAINWINDOW_H
