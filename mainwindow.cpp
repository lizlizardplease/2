#include "mainwindow.h"
#include "Initialization.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QString>



void MainWindow::run()

{
    m_model->setQuery(ui->todo->toPlainText());
    if (m_model->lastError().isValid())
        ui->er->setText("Ошибка: " + m_model->lastError().text());
    else{
        ui->tables->clear();
        ui->tables->addItems(m_db.tables());
        ui->todo->setText(" ");
    }
    ui->er->setText("Подсказка: кликните по таблице, которую хотите посмотреть!");
}
void MainWindow::away()
{
    if (dialog->exec() == QDialog::Accepted){
        ui->tables->clear();
        ui->tables->addItems(m_db.tables());
        m_model->clear();
    }
}
MainWindow::MainWindow(QSqlDatabase& db, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->run, SIGNAL(clicked()), this, SLOT(run()));
    connect(ui->run_2, SIGNAL(clicked()), this, SLOT(away()));
    m_db = db;
    dialog = new Initialization(m_db);
    if (!m_db.open())
    {
        ui->er->setText("Error: " + m_model->lastError().text());
    }
    m_model=new QSqlQueryModel;
    ui->tableView->setModel(m_model);
    ui->tables->addItems(m_db.tables());

    file.setFileName("logs.txt");
    file.open(QIODevice::ReadWrite);
    ui->textBrowser->setText(file.readAll());
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->run, SIGNAL(clicked()), this, SLOT(run()));
    connect(ui->run_2, SIGNAL(clicked()), this, SLOT(away()));
    m_db = QSqlDatabase::addDatabase("QPSQL");
    dialog = new Initialization(m_db);
    QSettings settings;
    settings.beginGroup("/Database_browser/settings");
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

    file.setFileName("logs.txt");
    file.open(QIODevice::ReadWrite);
    ui->textBrowser->setText(file.readAll());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tables_itemClicked(QListWidgetItem *item)
{
    m_model->setQuery("SELECT * FROM " + item->text());
}

