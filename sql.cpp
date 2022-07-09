/*This program is Licensed under the GNU GPL V3. This program uses Qt opensource
 * which uses the GPL V3, except for the Qt Sql library. The Qt Sql library is
 *licensed under the GNU LGPL V3 https://www.gnu.org/licenses/lgpl-3.0.html
 * This program also uses SQlite which is in the public domain, see sqlite.org for more information.*/
#include "sql.h"
#include "mainwindow.h"
#include <QString>
#include <QSql>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QFile>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

int spotting, flow, mood, sex, cramps, tender, headache;
QString DateFormats = "MM/dd/yy";
QDate cur_Date;
QString password = "";
bool passwordProtected = false;
bool startup = true;
bool symptoms[5];
int daysOut[5];

QSqlDatabase db;
//emits signal to update user interface on app startup
void sql::changer() {
    emit load();
}

void sql::Startup() {
    startup = true;
    QString dbName = "period_underground.sqlite";
    QString dbLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    //set database to store in users "Documents folder". On Mobile this will stay with the programs sandbox
    if(db.isDriverAvailable("SQLITECIPHER") == false) {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    else {
        db = QSqlDatabase::addDatabase("SQLITECIPHER");
    }
    db.setDatabaseName(dbLocation + "/" +dbName);
    db.database(dbLocation + "/" +dbName);
    db.databaseName();
    db.setPassword(password);

    if( QFile::exists(db.databaseName()))
    {

        //open database, read all user info and update user interface with new information
        if(db.open())
        {
            QSqlQuery query(db);
            //add settings table for existing databases
            query.prepare("CREATE TABLE IF NOT EXISTS Settings (ID int not null primary key, DateFormat text, noPassword int)");
            query.exec();
            //load data
            query.prepare("SELECT * FROM Period_Info");
            query.exec();
            int i = 0;
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
                i++;

        }

            //load settings
            query.prepare("SELECT * FROM Settings WHERE ID = (:ID)");
            query.bindValue(0, 1);
            query.exec();
            query.next();
            if(query.value(1).toString() != "") {
                DateFormats = query.value(1).toString();
            }

            else{//leave at default
            }

            }
        else
        {

        }

        QSqlQuery query(db);
        query.prepare("SELECT * FROM Settings WHERE ID = 1");
        query.exec();
        query.next();
        //check if password is needed
        if(query.value(2).toInt() < 1) {
            passwordProtected = true;
        }
    }
    //create new tables for stored data
    else {
        db.open();
        QSqlQuery query(db);
        query.prepare("CREATE TABLE IF NOT EXISTS Period_Info (QDate text not null primary key, flow int, mood int, sex int, spotting int, cramps int, tender int, headache int);");
        query.exec();
        query.prepare("CREATE TABLE IF NOT EXISTS Last_Period (QDate text not null primary key);");
        query.exec();
        query.prepare("CREATE TABLE IF NOT EXISTS Settings (ID int not null primary key, DateFormat text, noPassword int)");
        query.exec();
        query.prepare("INSERT INTO Settings (ID, noPassword) VALUES (:ID, :noPassword)");
        query.bindValue(":ID", 1);
        query.bindValue(":noPassword", 1);
        query.exec();

        //error checking
        if(!db.isOpen()) {
        }
}
    startup = false;
    db.close();
}
//save user input
void sql::saveData(QString date, int flow, int mood, int sex, int spotting, int crampsCheck, int tenderCheck, int headacheCheck) {
    //check if db is open
    if(db.isOpen() == false) {
        db.open();
    }

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
    if(startup == true) {}
    else {db.close();}

}
//load data pertaining to clicked date on calendar
void sql::loadData(QString curDate) {
    if(db.isOpen() == false) {
        db.open();
    }
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Period_Info WHERE QDate = (:QDate)");
    query.bindValue(":QDate", curDate);

    query.exec();
    query.next();
    flow = query.value(1).toInt();
    mood = query.value(2).toInt();
    sex = query.value(3).toInt();
    spotting = query.value(4).toInt();
    cramps = query.value(5).toInt();
    tender = query.value(6).toInt();
    headache = query.value(7).toInt();

    if(startup == true) {}
    else {db.close();}

}
//leave sql database file intact, but delete all user data from database
void sql::deleteALL(){
    if(db.isOpen() == false) {
        db.open();
    }
    QSqlQuery query(db);
    //delete all rows
    query.prepare("DELETE FROM Period_Info");
    query.exec();
    query.prepare("DELETE FROM Last_Period");
    query.exec();
    query.prepare("DELETE FROM Settings");
    query.exec();
    //vacuum database to ensure no data is left behind
    query.prepare("VACUUM");
    query.exec();
    db.close();
}
//find and return last period start date
QDate sql::lastPeriodCheck(){
    if(db.isOpen() == false) {
        db.open();
    }
    QSqlQuery query(db);
    query.prepare("SELECT QDate FROM Last_Period");
    query.exec();
    query.last();
    QString transitory = query.value(0).toString();
    QDate lastDate = lastDate.fromString(transitory);
    if(startup == true) {}
    else {db.close();}
    return lastDate;
}
//add start of new period for period estimator
void sql::newPeriodDate(QDate date1) {
    if(db.isOpen() == false) {
        db.open();
    }
    QString dateSave = date1.toString();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Last_Period (QDate) VALUES (:QDate)");
    query.bindValue(":QDate", dateSave);
    query.exec();
    if(startup == true) {}
    else {db.close();}
}

//estimate next period
QDate sql::whenIsPeriod(QDate date2) {
    QDate date3 = date2;
    if(db.isOpen() == false) {
        db.open();
    }
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Last_Period");
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
            first = first.fromString(transit);
        }
        else if(i == 2){
            transit = query.value(0).toString();
            current = current.fromString(transit);
            daysBetween = daysBetween + first.daysTo(current);
            first = current;
        }
        else {
            first = current;
            transit = query.value(0).toString();
            current = current.fromString(transit);
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
    if(startup == true) {}
    else {db.close();}

    return(date2);
}

void sql::saveSettings(QString dateFormat) {
    if(db.isOpen() == false) {
        db.open();
    }
    QSqlQuery query(db);
    //check for already existing rows
    query.prepare("SELECT * FROM Settings");
    query.exec();
    query.next();
    //if data doesn't exist add new data (this includes all check boxes under the calendar)
    if(query.value(0).toString() == ""){
        query.prepare("INSERT INTO Settings (ID, DateFormat) VALUES (:ID, :Date)");
        query.bindValue(0, 1);
        query.bindValue(1, dateFormat);
        query.exec();
    }
    //update changes to already existing information on current date
    else {
        query.prepare("UPDATE Settings SET DateFormat=:Date WHERE ID=:ID");
        query.bindValue(":Date", dateFormat);
        query.bindValue(":ID", 1);
        query.exec();
    }
    if(startup == true) {}
    else {db.close();}

}

void sql::createPassword(QString newPassword) {
    db.setPassword(newPassword);
    db.setConnectOptions("QSQLITE_BUSY_TIMEOUT=5000;QSQLITE_CREATE_KEY");
    db.open();
    db.close();
    password = newPassword;
    db.setPassword(password);
}

void sql::updatePassword(QString newPassword) {
    db.setPassword(password);
    QString command = "QSQLITE_UPDATE_KEY=" + newPassword;
    db.setConnectOptions(command);
    db.open();
    db.close();
    password = newPassword;
    db.setPassword(password);
}

void sql::removePassword() {
    db.setPassword(password);
    db.setConnectOptions("QSQLITE_REMOVE_KEY");
    db.open();
    db.close();
    password = "";
    db.setPassword(password);
}

bool sql::wasBleeding(QDate curDate) {
    int i = 10;
    bool blood = false;
    if(db.isOpen() == false) {
        db.open();
    }
    QSqlQuery query(db);
    while(i > 0) {
        QString cur_Date = curDate.toString();
        query.prepare("SELECT * FROM Period_Info WHERE QDate = (:QDate)");
        query.bindValue(":QDate", cur_Date);
        query.exec();
        query.next();
        int flow = query.value(1).toInt();
        if(flow >= 1) {
            blood = true;
        }
        curDate = curDate.addDays(-1);
        i = i-1;
    }
    if(startup == true) {}
    else {db.close();}
    return blood;
}

void sql::symptomEstimator() {
    //iterate through symptoms specifically, and create booleans for each
    // mood, spotting, cramps, tender, headache.
    symptoms[0] = false;
    symptoms[1] = false;
    symptoms[2] = false;
    symptoms[3] = false;
    symptoms[4] = false;
    daysOut[0] = 0;
    daysOut[1] = 0;
    daysOut[2] = 0;
    daysOut[3] = 0;
    daysOut[4] = 0;
    if(db.isOpen() == false) {
        db.open();
    }
    QSqlQuery query(db);
    QSqlQuery query2(db);
    query.prepare("SELECT * FROM Last_Period");
    query.exec();
    int daysOutAverage[5];
    daysOutAverage[0] = 0;
    daysOutAverage[1] = 0;
    daysOutAverage[2] = 0;
    daysOutAverage[3] = 0;
    daysOutAverage[4] = 0;
    while(query.next()) {
        int howMany = -1;
       //initialize average counting

        QString date = query.value(0).toString();
        QDate date1 = date1.fromString(date);
        //this point on needs modification, how are we checking days out? assume while loop but then what?
        while(howMany > -8) {
            qDebug() << "Second while loop";
            date1 = date1.addDays(-1);
            query2.prepare("SELECT * FROM Period_Info WHERE QDate = (:QDate)");
            query2.bindValue(":QDate", date1.toString());
            query2.exec();
            query2.next();
            //check which mood in particular?
            if(query2.value(2).toInt() > 0) {
                daysOut[0] = daysOut[0] + howMany;
                daysOutAverage[0] = daysOutAverage[0]+1;
                symptoms[0] = true;
            }
            if(query2.value(4).toInt() > 0) {
                daysOut[1] = daysOut[1] + howMany;
                daysOutAverage[1] = daysOutAverage[1]+1;
                symptoms[1] = true;
            }
            if(query2.value(5).toInt() > 0) {
                daysOut[2] = daysOut[2] + howMany;
                daysOutAverage[2] = daysOutAverage[2]+1;
                symptoms[2] = true;
            }
            if(query2.value(6).toInt() > 0) {
                daysOut[3] = daysOut[3] + howMany;
                daysOutAverage[3] = daysOutAverage[3]+1;
                symptoms[3] = true;
            }
            if(query2.value(7).toInt() > 0) {
                daysOut[4] = daysOut[4] + howMany;
                daysOutAverage[4] = daysOutAverage[4]+1;
                symptoms[4] = true;
            }
            howMany = howMany-1;
        }

    }
    int i = 0;
    while(i < 5) {
        if(symptoms[i] == true && daysOut[i] != 0) {
            daysOut[i] = daysOut[i] / daysOutAverage[i];
            i++;
        }
        i++;
    }
    if(startup == true) {}
    else {db.close();}
}
