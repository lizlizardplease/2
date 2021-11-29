#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql>
#include <QListWidget>

class Initialization;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class Initialization; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(QSqlDatabase& db, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void run();
    void away();
    void on_tables_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QFile file;
    Initialization* dialog;
    QSqlQueryModel *m_model;
    QSqlDatabase m_db;
};
#endif // MAINWINDOW_H
