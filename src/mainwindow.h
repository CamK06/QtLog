#pragma once

#include <QMainWindow>

#include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void onLogEntrySelected(int row, int column);
    void onAddQsoButtonClicked();

private:
    void setLogRow(int row, QDate date, QTime time, QString callsign, float frequency, QString mode, QString comment);

    Ui::MainWindow *ui;
    bool hasSelectedEntry = false;
};