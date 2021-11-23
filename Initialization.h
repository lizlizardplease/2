#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "mainwindow.h"
#include <QWidget>
#include <QDialog>
#include <QSqlDatabase>
#include <QFile>
#include <QDateTime>

namespace Ui {
class Initialization;
}

class Initialization : public QDialog
{
    Q_OBJECT

public:
    explicit Initialization(QSqlDatabase& db);
    ~Initialization();

private slots:
    void on_pushButton_clicked();

private:
    QSqlDatabase& m_db;
    Ui::Initialization *ui;
    QFile file_conn;
    QFile inf;
    QDateTime time2;
};

#endif // INITIALIZATION_H
