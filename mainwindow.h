#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql>

class Initialization;

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
    void run();
    void away();
private:
    Ui::MainWindow *ui;
    Initialization* dialog;
    QSqlQueryModel *m_model;
    QSqlDatabase m_db;
};
#endif // MAINWINDOW_H
