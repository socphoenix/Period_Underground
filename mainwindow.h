/*This program is Licensed under the GNU GPL V3 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calendarWidget_selectionChanged();

    void on_pushButton_clicked();

    void on_comboBox_3_currentIndexChanged(int index);

    void on_calendarWidget_activated(const QDate &date);

    void on_textEdit_selectionChanged();

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_cursorPositionChanged();

    void on_textEdit_redoAvailable(bool b);

    void on_textEdit_textChanged();

    void on_textEdit_undoAvailable(bool b);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_4_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

public slots:
    void updateUI();
    //need to create a signal/slot to update UI from reading of sql

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H