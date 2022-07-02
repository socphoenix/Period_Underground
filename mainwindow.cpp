/*This program is Licensed under the GNU GPL V3 */
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDate"
#include "sql.h"
#include <QTextCharFormat>
#include <QWidget>
#include <QObject>
#include <QMessageBox>
#include <QColor>
sql f;
QTextCharFormat currentDateColor;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&f, SIGNAL(load()), this, SLOT(updateUI()));
    //set default color in case spotting is unselected to No
    QColor testing;
    testing = ui->comboBox->palette().base().color();
    currentDateColor.setBackground(QColor(testing));
    f.Startup();
    QDate test = f.lastPeriodCheck();
    QDate test1;
    if(test != test1) {
        QDate nextPeriod = f.whenIsPeriod(test);
        int i = 0;
        ui->label_5->setText(nextPeriod.toString("MM/dd/yy"));
        ui->label_7->setText(test.toString("MM/dd/yy"));
        while(i < 7){
            QTextCharFormat format;
            format.setBackground(QColor("green"));
            ui->calendarWidget->setDateTextFormat(nextPeriod, format);
            nextPeriod = nextPeriod.addDays(1);
            i++;
        }

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

//function to update calendar on app startup
void MainWindow::updateUI() {
    ui->calendarWidget->setSelectedDate(cur_Date);
    ui->comboBox->setCurrentIndex(spotting);
    ui->comboBox_3->setCurrentIndex(flow);
    ui->comboBox_2->setCurrentIndex(mood);
    ui->comboBox_4->setCurrentIndex(sex);
    ui->checkBox->setChecked(cramps);
    ui->checkBox_2->setChecked(tender);
    ui->checkBox_3->setChecked(headache);
    if(flow == 1){
        QTextCharFormat format;
        format.setBackground(QColor("salmon"));
        QDate sql_me = ui->calendarWidget->selectedDate();
        ui->calendarWidget->setDateTextFormat(sql_me, format);
    }
    else if(flow == 2) {
        QTextCharFormat format;
        format.setBackground(QColor("red"));
        QDate sql_me = ui->calendarWidget->selectedDate();
        ui->calendarWidget->setDateTextFormat(sql_me, format);
    }
    else if(flow == 3) {
        QTextCharFormat format;
        format.setBackground(QColor("maroon"));
        QDate sql_me = ui->calendarWidget->selectedDate();
        ui->calendarWidget->setDateTextFormat(sql_me, format);
    }
    else if(spotting == 1) {
        QTextCharFormat format;
        format.setBackground(QColor("grey"));
        QDate sql_me = ui->calendarWidget->selectedDate();
        ui->calendarWidget->setDateTextFormat(sql_me, format);
        }
    else{}//last else to just return null

}
//get values for period info on selected date
void MainWindow::on_calendarWidget_selectionChanged()
{
    QDate cur_Date = ui->calendarWidget->selectedDate();
    QString curDate = cur_Date.toString();
    f.loadData(curDate);
    ui->comboBox_3->setCurrentIndex(flow);
    ui->comboBox_2->setCurrentIndex(mood);
    ui->comboBox_4->setCurrentIndex(sex);
    ui->comboBox->setCurrentIndex(spotting);
    ui->checkBox->setChecked(cramps);
    ui->checkBox_2->setChecked(tender);
    ui->checkBox_3->setChecked(headache);

}


void MainWindow::on_pushButton_clicked()
{
    //kill all humans
    f.deleteALL();
    QMessageBox::information(
        this,
        tr("Application Name"),
        tr("All Data Successfully Deleted. The Program will now close.") );
    QCoreApplication::quit();
}


void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    if(index == 1){
        QTextCharFormat format;
        format.setBackground(QColor("salmon"));
        QDate sql_me = ui->calendarWidget->selectedDate();
        ui->calendarWidget->setDateTextFormat(sql_me, format);
        //ui->comboBox->setCurrentIndex(1);
    }
    else if (index == 2){
        QTextCharFormat format;
        format.setBackground(QColor("red"));
        QDate sql_me = ui->calendarWidget->selectedDate();
        ui->calendarWidget->setDateTextFormat(sql_me, format);
        //ui->comboBox->setCurrentIndex(1);
    }
    else if (index == 3){
        QTextCharFormat format;
        format.setBackground(QColor("maroon"));
        QDate sql_me = ui->calendarWidget->selectedDate();
        ui->calendarWidget->setDateTextFormat(sql_me, format);
        //ui->comboBox->setCurrentIndex(1);
    }
    else if(ui->comboBox->currentIndex() == 1) {
        QTextCharFormat format;
        format.setBackground(QColor("grey"));
        QDate sql_me = ui->calendarWidget->selectedDate();
        ui->calendarWidget->setDateTextFormat(sql_me, format);

    }
    else {
        QDate sql_me = ui->calendarWidget->selectedDate();
        ui->calendarWidget->setDateTextFormat(sql_me, currentDateColor);
    }
    QString curDate;
    QDate cur_Date = ui->calendarWidget->selectedDate();
    curDate = cur_Date.toString();
    int flow, mood, sex, spotting;
    int crampsCheck, tenderCheck, headacheCheck;
    flow = ui->comboBox_3->currentIndex();
    mood = ui->comboBox_2->currentIndex();
    sex = ui->comboBox_4->currentIndex();
    spotting = ui->comboBox->currentIndex();
    crampsCheck = ui->checkBox->checkState();
    tenderCheck = ui->checkBox_2->checkState();
    headacheCheck = ui->checkBox_3->checkState();
    f.saveData(curDate, flow, mood, sex, spotting, crampsCheck, tenderCheck, headacheCheck);
    //check if this is a new period
    QDate lastPeriod;
    QDate currentDate;
    QDate nextPeriod;
    currentDate = ui->calendarWidget->selectedDate();
    lastPeriod = f.lastPeriodCheck();
    if(lastPeriod < currentDate.addDays(-3) && flow != 0) {
        //add new period info
        f.newPeriodDate(currentDate);
        nextPeriod = f.whenIsPeriod(currentDate);
        ui->label_7->setText(currentDate.toString("MM/dd/yy"));
        ui->label_5->setText(nextPeriod.toString("MM/dd/yy"));
        int i = 0;
        while(i < 7){
            QTextCharFormat format;
            format.setBackground(QColor("green"));
            ui->calendarWidget->setDateTextFormat(nextPeriod, format);
            nextPeriod = nextPeriod.addDays(1);
            i++;
        }
    }
    else {/*no action needed*/}


}


void MainWindow::on_calendarWidget_activated(const QDate &date)
{
    QInputMethod* input = QGuiApplication::inputMethod();
    input->setVisible(false);
}


void MainWindow::on_textEdit_selectionChanged()
{
    QInputMethod* input = QGuiApplication::inputMethod();
    input->setVisible(false);
}


void MainWindow::on_textEdit_copyAvailable(bool b)
{
    QInputMethod* input = QGuiApplication::inputMethod();
    input->setVisible(false);
}


void MainWindow::on_textEdit_cursorPositionChanged()
{
    QInputMethod* input = QGuiApplication::inputMethod();
    input->setVisible(false);
}


void MainWindow::on_textEdit_redoAvailable(bool b)
{
    QInputMethod* input = QGuiApplication::inputMethod();
    input->setVisible(false);
}


void MainWindow::on_textEdit_textChanged()
{
    QInputMethod* input = QGuiApplication::inputMethod();
    input->setVisible(false);
}


void MainWindow::on_textEdit_undoAvailable(bool b)
{
    QInputMethod* input = QGuiApplication::inputMethod();
    input->setVisible(false);
}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    QString curDate;
    QDate cur_Date = ui->calendarWidget->selectedDate();
    curDate = cur_Date.toString();
    int flow, mood, sex, spotting;
    int crampsCheck, tenderCheck, headacheCheck;
    flow = ui->comboBox_3->currentIndex();
    mood = ui->comboBox_2->currentIndex();
    sex = ui->comboBox_4->currentIndex();
    spotting = ui->comboBox->currentIndex();
    crampsCheck = ui->checkBox->checkState();
    tenderCheck = ui->checkBox_2->checkState();
    headacheCheck = ui->checkBox_3->checkState();
    f.saveData(curDate, flow, mood, sex, spotting, crampsCheck, tenderCheck, headacheCheck);
}


void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    QString curDate;
    QDate cur_Date = ui->calendarWidget->selectedDate();
    curDate = cur_Date.toString();
    int flow, mood, sex, spotting;
    int crampsCheck, tenderCheck, headacheCheck;
    flow = ui->comboBox_3->currentIndex();
    mood = ui->comboBox_2->currentIndex();
    sex = ui->comboBox_4->currentIndex();
    spotting = ui->comboBox->currentIndex();
    crampsCheck = ui->checkBox->checkState();
    tenderCheck = ui->checkBox_2->checkState();
    headacheCheck = ui->checkBox_3->checkState();
    f.saveData(curDate, flow, mood, sex, spotting, crampsCheck, tenderCheck, headacheCheck);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{

    QString curDate;
    QDate cur_Date = ui->calendarWidget->selectedDate();
    curDate = cur_Date.toString();
    int flow, mood, sex, spotting;
    int crampsCheck, tenderCheck, headacheCheck;
    flow = ui->comboBox_3->currentIndex();
    mood = ui->comboBox_2->currentIndex();
    sex = ui->comboBox_4->currentIndex();
    spotting = ui->comboBox->currentIndex();
    crampsCheck = ui->checkBox->checkState();
    tenderCheck = ui->checkBox_2->checkState();
    headacheCheck = ui->checkBox_3->checkState();
    f.saveData(curDate, flow, mood, sex, spotting, crampsCheck, tenderCheck, headacheCheck);
    if(spotting == 1){
        QTextCharFormat format;
        format.setBackground(QColor("grey"));
        ui->calendarWidget->setDateTextFormat(cur_Date, format);
    }
    else {
        QDate sql_me = ui->calendarWidget->selectedDate();
        ui->calendarWidget->setDateTextFormat(sql_me, currentDateColor);
    }

}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    int crampsCheck, tenderCheck, headacheCheck;
    int flow, mood, sex, spotting;
    QDate curDate = ui->calendarWidget->selectedDate();
    QString cur_Date = curDate.toString();
    crampsCheck = ui->checkBox->checkState();
    tenderCheck = ui->checkBox_2->checkState();
    headacheCheck = ui->checkBox_3->checkState();
    flow = ui->comboBox_3->currentIndex();
    mood = ui->comboBox_2->currentIndex();
    sex = ui->comboBox_4->currentIndex();
    spotting = ui->comboBox->currentIndex();
    f.saveData(cur_Date, flow, mood, sex, spotting, crampsCheck, tenderCheck, headacheCheck);
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    int crampsCheck, tenderCheck, headacheCheck;
    int flow, mood, sex, spotting;
    QDate curDate = ui->calendarWidget->selectedDate();
    QString cur_Date = curDate.toString();
    crampsCheck = ui->checkBox->checkState();
    tenderCheck = ui->checkBox_2->checkState();
    headacheCheck = ui->checkBox_3->checkState();
    flow = ui->comboBox_3->currentIndex();
    mood = ui->comboBox_2->currentIndex();
    sex = ui->comboBox_4->currentIndex();
    spotting = ui->comboBox->currentIndex();
    f.saveData(cur_Date, flow, mood, sex, spotting, crampsCheck, tenderCheck, headacheCheck);
}


void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    int crampsCheck, tenderCheck, headacheCheck;
    int flow, mood, sex, spotting;
    QDate curDate = ui->calendarWidget->selectedDate();
    QString cur_Date = curDate.toString();
    crampsCheck = ui->checkBox->checkState();
    tenderCheck = ui->checkBox_2->checkState();
    headacheCheck = ui->checkBox_3->checkState();
    flow = ui->comboBox_3->currentIndex();
    mood = ui->comboBox_2->currentIndex();
    sex = ui->comboBox_4->currentIndex();
    spotting = ui->comboBox->currentIndex();
    f.saveData(cur_Date, flow, mood, sex, spotting, crampsCheck, tenderCheck, headacheCheck);
}

