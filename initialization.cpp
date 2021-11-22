#include "initialization.h"
#include "ui_initialization.h"

Initialization::Initialization(QSqlDatabase& db) :
    QDialog(),
    m_db(db),
    ui(new Ui::Initialization)
{
    ui->setupUi(this);
    file_conn.setFileName("Connections.txt");
    file_conn.open(QIODevice::ReadOnly);
    inf.setFileName("temp.txt");
    inf.open(QIODevice::Append);
}


Initialization::~Initialization()
{
    delete ui;
}

void Initialization::on_pushButton_clicked()
{
    //проверка на заполнение
    if(ui->lineEdit_ip->text() == "" || ui->lineEdit_password->text() == ""|| ui->lineEdit_db_name->text() == "" || ui->lineEdit_port->text() == "" || ui->lineEdit_login->text() == ""){
        ui->errrlab->setText("Please, fill in all input fields");
    }
    else{
        //проверка на правильный ввод
        QTextStream out(&inf);
        time2 = QDateTime::currentDateTime();

        bool flag_pass = false;
        bool new_user = true;

        QTextStream in(&file_conn);
        in.seek(0);
        QString line = in.readLine();
        while (!line.isNull()) {
            if(line == ui->lineEdit_login->text()){
                new_user = false;
                line = in.readLine();
                if(line == ui->lineEdit_password->text()){
                    flag_pass = true;
                }
            }
            line = in.readLine();
        }
        if(flag_pass == false && new_user == false)
            ui->errrlab->setText("Incorrect login or password");
        else{

            m_db.setDatabaseName(ui->lineEdit_db_name->text());
            m_db.setHostName(ui->lineEdit_ip->text());
            m_db.setPassword(ui->lineEdit_password->text());
            m_db.setPort(ui->lineEdit_port->text().toInt());
            m_db.setUserName(ui->lineEdit_login->text());

            file_conn.close();
            inf.open(QIODevice::Append);
            out << time2.toString("[dd.MM.yy , hh:mm:ss] -> ")
                       + ui->lineEdit_db_name->text() + '\n'
                       + ui->lineEdit_ip->text() + '\n'
                       + ui->lineEdit_port->text() + '\n'
                       + ui->lineEdit_login->text() + '\n'
                       + ui->lineEdit_password->text() + '\n' + '\n';


            if(m_db.isOpen())

                accept();

            else
               ui->errrlab->setText(m_db.lastError().text());
            file_conn.close();

        }
    }
}
