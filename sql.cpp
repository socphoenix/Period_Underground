/*This program is Licensed under the GNU GPL V3 */
#include "sql.h"
#include "mainwindow.h"
#include <QString>
#include <QSql>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QFile>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

int spotting, flow, mood, sex, cramps, tender, headache;
QDate cur_Date;

QSqlDatabase db;
//emits signal to update user interface on app startup
void sql::changer() {
    emit load();
}

void sql::Startup() {
    QString dbName = "period_underground.sqlite";
    QString dbLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    //set database to store in users "Documents folder". On Mobile this will stay with the programs sandbox
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbLocation + "/" +dbName);
    db.database(dbLocation + "/" +dbName);
    db.databaseName();

    if( QFile::exists(db.databaseName()))
    {

        qDebug()<<"DATABASE EXIST";
        //open database, read all user info and update user interface with new information
        if(db.open())
        {
            QSqlQuery query(db);
            query.prepare("SELECT * FROM Period_Info");
            query.exec();
            while(query.next()) {
                //cycle through all and paint as needed, reference main window?
                QString curDate = query.value(0).toString();
                cur_Date = cur_Date.fromString(curDate);
                flow = query.value(1).toInt();
                mood = query.value(2).toInt();
                sex = query.value(3).toInt();
                spotting = query.value(4).toInt();
                cramps = query.value(5).toInt();
                tender = query.value(6).toInt();
                headache = query.value(7).toInt();
                changer();

        }
            //calculate next period and update
            //need to get period start data in Last_Period table somehow

            qDebug() << "DATABASE OPEN";
            }
        else
        {
            qDebug() << "DATABASE CLOSED";
        }
    }
    //create new tables for stored data
    else {
        qDebug() << "NO EXISTING DATABASE, CREATING ONE";
        db.open();
        QSqlQuery query(db);
        query.prepare("CREATE TABLE IF NOT EXISTS Period_Info (QDate text not null primary key, flow int, mood int, sex int, spotting int, cramps int, tender int, headache int);");
        query.exec();
        query.prepare("CREATE TABLE IF NOT EXISTS Last_Period (QDate text not null primary key);");
        query.exec();

        //error checking
        if(!db.isOpen()) {
            qDebug() << "ERROR I CAN'T OPEN DATABASE";
        }
}
}
//save user input
void sql::saveData(QString date, int flow, int mood, int sex, int spotting, int crampsCheck, int tenderCheck, int headacheCheck) {

    QSqlQuery query(db);
    //check for already existing rows
    query.prepare("SELECT * FROM Period_Info WHERE QDate = (:QDate)");
    query.bindValue(":QDate", date);
    query.exec();
    query.next();
    //if data doesn't exist add new data (this includes all check boxes under the calendar)
    if(query.value(0).toString() == ""){
        query.prepare("INSERT INTO Period_Info (QDate, flow, mood, sex, spotting, cramps, tender, headache) VALUES (:QDate, :flow, :mood, :sex, :spotting, :cramps, :tender, :headache)");
        query.bindValue(0, date);
        query.bindValue(1, flow);
        query.bindValue(2, mood);
        query.bindValue(3, sex);
        query.bindValue(4, spotting);
        query.bindValue(5, crampsCheck);
        query.bindValue(6, tenderCheck);
        query.bindValue(7, headacheCheck);
        query.exec();
    }
    //update changes to already existing information on current date
    else {
        query.prepare("UPDATE Period_Info SET flow=:flow, mood=:mood, sex=:sex, spotting=:spotting, cramps=:cramps, tender=:tender, headache=:headache WHERE QDate=:QDate");
        query.bindValue(":flow", flow);
        query.bindValue(":mood", mood);
        query.bindValue(":sex", sex);
        query.bindValue(":spotting", spotting);
        query.bindValue(":cramps", crampsCheck);
        query.bindValue(":tender", tenderCheck);
        query.bindValue(":headache", headacheCheck);
        query.bindValue(":QDate", date);
        query.exec();
    }

}
//load data pertaining to clicked date on calendar
void sql::loadData(QString curDate) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Period_Info WHERE QDate = (:QDate)");
    query.bindValue(":QDate", curDate);

    query.exec();
    query.next();
    QString debug = query.value(0).toString();
    qDebug() << debug;
    flow = query.value(1).toInt();
    qDebug() << flow;
    mood = query.value(2).toInt();
    qDebug() << mood;
    sex = query.value(3).toInt();
    qDebug() << sex;
    spotting = query.value(4).toInt();
    qDebug() << spotting;
    cramps = query.value(5).toInt();
    tender = query.value(6).toInt();
    headache = query.value(7).toInt();

}
//leave sql database file intact, but delete all user data from database
void sql::deleteALL(){
    QSqlQuery query(db);
    query.prepare("DELETE FROM Period_Info");
    query.exec();
    query.prepare("DELETE FROM Last_Period");
    query.exec();
}
//find and return last period start date
QDate sql::lastPeriodCheck(){
    QSqlQuery query(db);
    query.prepare("SELECT QDate FROM Last_Period");
    query.exec();
    query.last();
    QString transitory = query.value(0).toString();
    QDate lastDate = lastDate.fromString(transitory);
    return lastDate;
}
//add start of new period for period estimator
void sql::newPeriodDate(QDate date1) {
    QString dateSave = date1.toString();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Last_Period (QDate) VALUES (:QDate)");
    query.bindValue(":QDate", dateSave);
    query.exec();
}

//estimate next period
QDate sql::whenIsPeriod(QDate date2) {
    QSqlQuery query(db);
    query.prepare("SELECT QDate FROM Last_Period");
    query.exec();
    int i = 0;
    int daysBetween = 0;
    QDate first;
    QDate current;
    QString transit;
    while(query.next()) {
        i++;
        if(i < 2) {
            transit = query.value(0).toString();
            first.fromString(transit);
        }
        else if(i == 2){
            transit = query.value(0).toString();
            current.fromString(transit);
            daysBetween = first.daysTo(current);
        }
        else {
            first = current;
            transit = query.value(0).toString();
            current.fromString(transit);
            daysBetween = daysBetween + first.daysTo(current);
        }
    }
    if(i > 5) {
        daysBetween = daysBetween / i;
        date2 = date2.addDays(daysBetween);
    }
    else {
        date2 = date2.addDays(28);
    }
    qDebug() << date2;
    return(date2);
}
