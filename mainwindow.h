#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "initialization.h"
#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class Initialization; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void nashSlot(); // это созданный нами слот
private:
    Ui::MainWindow *ui;
    QSqlQueryModel *m_model;
    QSqlDatabase m_db;
};
#endif // MAINWINDOW_H
