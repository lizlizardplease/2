#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>



void MainWindow::nashSlot()

{
    QSqlQuery query(m_db);
    std::string command;
    QSqlRecord rec;
    command = ui->todo->toPlainText().toStdString(); // получаем строку из первого QLineEdit
    if (command == "exit"){}
    if (!query.exec(command.c_str()))
    {
        ui->er->setText("Ошибка: непонятно, чего вы хотите сделать.");
    }
    if (!query.isSelect())
    {
        ui->er->setText("Сделано.");
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    Initialization* dialog = new Initialization(m_db);
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

    delete dialog;
}

MainWindow::~MainWindow()
{
    delete ui;
}

