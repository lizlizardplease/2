#include "Initialization.h"
#include "ui_Initialization.h"


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
    //connect(ui->pb, SIGNAL(clicked()), this, SLOT(on_pb_clicked()));
    QSettings settings;
    settings.beginGroup("/Database_browser/settings");
    ui->lineEdit_db_name->setText     (settings.value("Database_name", "fn1131_2021" ).toString());
    ui->lineEdit_ip->setText       (settings.value("Host_ip"      , "195.19.32.74").toString());
    ui->lineEdit_port->setText     (settings.value("P0rt"         , 5432          ).toString());
    ui->lineEdit_login->setText    (settings.value("L0g1n"        , "student"     ).toString());
    ui->lineEdit_password->setText (settings.value("Password"     , "bmstu"       ).toString());
    settings.sync();
    settings.endGroup();
}

Initialization::~Initialization()
{
    delete ui;
}

void Initialization::on_pb_clicked()
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
            //inf.open(QIODevice::Append);
            out << time2.toString("[dd.MM.yy , hh:mm:ss] -> ")
                       + ui->lineEdit_db_name->text() + '\n'
                       + ui->lineEdit_ip->text() + '\n'
                       + ui->lineEdit_port->text() + '\n'
                       + ui->lineEdit_login->text() + '\n'
                       + ui->lineEdit_password->text() + '\n' + '\n';
                if(m_db.open()){
                    QSettings settings;
                    settings.beginGroup("/Database_browser/settings");
                    settings.setValue("Database_name", ui->lineEdit_db_name->text()    );
                    settings.setValue("Host_ip"      , ui->lineEdit_ip->text()     );
                    settings.setValue("P0rt"         , ui->lineEdit_port->text()    );
                    settings.setValue("L0g1n"        , ui->lineEdit_login->text()   );
                    settings.setValue("Password"     , ui->lineEdit_password->text());
                    settings.sync();
                    qDebug() << settings.fileName();
                    settings.endGroup();
                }
               if(m_db.isOpen()){
                accept();
}
            else
               ui->errrlab->setText(m_db.lastError().text());
            file_conn.close();

        }
    }
}

