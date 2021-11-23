#include "mainwindow.h"
#include "Initialization.h"
#include "ui_mainwindow.h"
#include <QDateTime>



void MainWindow::run()

{
   ui->er->setText("Ошибка: непонятно, чего вы хотите сделать.");
}
void MainWindow::away()

{
    dialog->show();
    this->close();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    dialog = new Initialization(m_db);
    ui->setupUi(this);
    connect(ui->run, SIGNAL(clicked()), this, SLOT(run()));
    connect(ui->run_2, SIGNAL(clicked()), this, SLOT(away()));
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QSettings settings;
    m_db.setDatabaseName(settings.value("Database_name", "fn1131_2021").toString());
    m_db.setHostName(settings.value("Host_ip", "195.19.32.74").toString());
    m_db.setPort(settings.value("P0rt", 5432).toInt());
    m_db.setUserName(settings.value("L0gin", "student").toString());
    m_db.setPassword(settings.value("Password", "bmstu").toString());
    settings.endGroup();

    if (!m_db.open())
    {
        ui->er->setText("Error: " + m_model->lastError().text());
    }
    m_model=new QSqlQueryModel;
    ui->tableView->setModel(m_model);
    ui->tables->addItems(m_db.tables());

    /*file.setFileName("logs.txt");
    file.open(QIODevice::ReadWrite);
    ui->logsTextBrowser->setText(file.readAll());*/

    //delete dialog;
}

MainWindow::~MainWindow()
{
    delete ui;
}

