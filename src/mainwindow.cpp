#include <spdlog/spdlog.h>
#include <QMessageBox>

#include "mainwindow.h"
#include "version.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    spdlog::info("QtLog " VERSION);

    ui->setupUi(this);
    
    ui->logbookTable->insertRow(1);
    setLogRow(1, QDate::currentDate(), QTime::currentTime(), "N0CALL", 14.070, "SSB", "Hello World!");

    // Signals
    connect(ui->logbookTable, &QTableWidget::cellClicked, this, &MainWindow::onLogEntrySelected);
    connect(ui->addQsoButton, &QPushButton::clicked, this, &MainWindow::onAddQsoButtonClicked);

    spdlog::info("Initialized main window");
}

void MainWindow::onAddQsoButtonClicked() 
{
    // If no callsign was given, throw an error
    if(ui->newCallLine->text().isEmpty()) {
        QMessageBox errorMsg;
        errorMsg.critical(0, "Error", "Callsign cannot be empty");
        errorMsg.setFixedSize(500, 200);
        return;
    }

    // Add the new QSO to the log and select it so it can be edited
    ui->logbookTable->insertRow(0);
    setLogRow(0, QDate::currentDate(), QTime::currentTime(), ui->newCallLine->text(), 0.0f, "SSB", "");
    ui->logbookTable->selectRow(0);
    ui->logbookTable->cellClicked(0, 1);
    ui->newCallLine->clear();
}

void MainWindow::onLogEntrySelected(int row, int column)
{
    // This code s u c k s but works
    if(!hasSelectedEntry) {
        hasSelectedEntry = true;
        ui->qsoCallInput->setEnabled(true);
        ui->qsoDateEdit->setEnabled(true);
        ui->qsoTimeEdit->setEnabled(true);
        ui->qsoTimeNow->setEnabled(true);
        ui->qsoBand->setEnabled(true);
        ui->qsoMode->setEnabled(true);
        ui->qsoFreq->setEnabled(true);
        ui->qsoRSTRecd->setEnabled(true);
        ui->qsoRSTSent->setEnabled(true);
        ui->qsoPower->setEnabled(true);
    }

    ui->qsoDateEdit->setDate(ui->logbookTable->item(row, 0)->data(Qt::DisplayRole).toDate());
    ui->qsoTimeEdit->setTime(ui->logbookTable->item(row, 1)->data(Qt::DisplayRole).toTime());
    ui->qsoCallInput->setText(ui->logbookTable->item(row, 2)->text());
    ui->qsoFreq->setText(ui->logbookTable->item(row, 3)->text());
}

void MainWindow::setLogRow(int row, QDate date, QTime time, QString callsign, float frequency, QString mode, QString comment)
{
    ui->logbookTable->setItem(row, 0, new QTableWidgetItem(date.toString("yyyy-MM-dd")));
    ui->logbookTable->setItem(row, 1, new QTableWidgetItem(time.toString("hh:mm")));
    ui->logbookTable->setItem(row, 2, new QTableWidgetItem(callsign));
    ui->logbookTable->setItem(row, 3, new QTableWidgetItem(QString::number(frequency)));
    ui->logbookTable->setItem(row, 4, new QTableWidgetItem(mode));
    ui->logbookTable->setItem(row, 5, new QTableWidgetItem(comment));
}