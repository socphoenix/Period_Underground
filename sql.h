/*This program is Licensed under the GNU GPL V3. This program uses Qt opensource
 * which uses the GPL V3, except for the Qt Sql library. The Qt Sql library is
 *licensed under the GNU LGPL V3 https://www.gnu.org/licenses/lgpl-3.0.html
 * This program also uses SQlite which is in the public domain, see sqlite.org for more information.*/
#ifndef SQL_H
#define SQL_H

#include <QDate>
#include <QSql>
#include <QString>
#include <QObject>

extern int spotting, flow, mood, sex, cramps, tender, headache, noAverage, clearCache;
extern QDate cur_Date;
extern QString DateFormats, password;
extern bool passwordProtected;
extern bool symptoms[5];
extern int daysOut[5];
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
    void demoMode();
    void reload();
    void clearCalendar();
    QDate lastPeriodCheck();
    void newPeriodDate(QDate date1);
    QDate whenIsPeriod(QDate date2);
    void saveSettings(QString dateFormat);
    void createPassword(QString newPassword);
    void updatePassword(QString newPassword);
    void removePassword();
    bool wasBleeding(QDate curDate);
    void symptomEstimator();
    void noAverages(int number);

signals:
    void load();
};


#endif // SQL_H
