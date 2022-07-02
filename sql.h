/*This program is Licensed under the GNU GPL V3 */
#ifndef SQL_H
#define SQL_H

#include <QDate>
#include <QSql>
#include <QString>
#include <QObject>

extern int spotting, flow, mood, sex, cramps, tender, headache;
extern QDate cur_Date;
extern QString DateFormats;

class sql : public QObject
{
    Q_OBJECT;
public:
    sql() {};

public slots:
    void Startup();
    void saveData(QString date, int flow, int mood, int sex, int spotting, int crampsCheck, int tenderCheck, int headacheCheck);
    void loadData(QString curDate);
    void changer();
    void deleteALL();
    QDate lastPeriodCheck();
    void newPeriodDate(QDate date1);
    QDate whenIsPeriod(QDate date2);
    void saveSettings(QString dateFormat);

signals:
    void load();
};


#endif // SQL_H
