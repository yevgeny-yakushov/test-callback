#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pQueryImpl = new CQueryImpl();

    connect(ui->m_btnExecute, &QPushButton::clicked, this, &MainWindow::execute);
}

MainWindow::~MainWindow()
{
    delete m_pQueryImpl; m_pQueryImpl = nullptr;
    delete ui;
}

void MainWindow::execute()
{
    m_pQueryImpl->startTest(123, 456);
}

