/*
 *  Copyright (C) 2021 realth000 <a598919335@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "btmainwindow.h"
#include "./ui_btmainwindow.h"

#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "core/backupprogressworker.h"
#include "core/jsonparser.h"

#define WINDOW_MIN_WIDTH  1000
#define WINDOW_MIN_HEIGHT 700

#define BACKUP_TABLE_ROW_HEIGHT 35

BTMainWindow::BTMainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::BTMainWindow),
      m_controller(new BTMainController(this)),
      m_backupConfigs(new BackupConfigDatas),
      m_backupChBVector(new QVector<QCheckBox *>),
      m_bakChBCheckedCount(0)
{
    ui->setupUi(this);
    loadConfig();
    initConnection();
    initUI();
}

BTMainWindow::~BTMainWindow()
{
    delete ui;
    delete m_backupConfigs;
    qDeleteAll(*m_backupChBVector);
    delete m_backupChBVector;
}

void BTMainWindow::loadConfig()
{
    // test
#if 0
    BackupConfigObject outObj;
    outObj.id = "1";
    outObj.name = "test";
    outObj.lastBackupTime = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    outObj.srcPath = "C:/QtProjects/0/test";
    outObj.dstPath = "C:/QtProjects/0/testdst";
    QVector<BackupConfigObject> outVector;
    outVector.append(outObj);
    JsonParser::saveBackupConfigJsonToFile("C:/QtProjects/0/backupConfig", outVector);
#endif
    JsonParser::loadBackupConfigJsonFromFile("C:/QtProjects/0/backupConfig", m_backupConfigs);
    qDebug() << "load result:" << JsonParser::backupConfigToString(*m_backupConfigs);
}

void BTMainWindow::initConnection()
{
    // startBackupPushButton
    connect(ui->startBackupPushButton, &QPushButton::clicked, this, &BTMainWindow::startBackupProgress);
}

void BTMainWindow::initUI()
{
    initWindow();
    initBackupTable();
    loadBackupConfigToTable();

}

void BTMainWindow::initWindow()
{
    this->setMinimumSize(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
}

void BTMainWindow::initBackupTable()
{
    const int backupConfigCount = m_backupConfigs->length();
    if(backupConfigCount <= 0){
        return;
    }

    ui->backupTable->clearContents();
    ui->backupTable->setRowCount(0);
    ui->backupTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->backupTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->backupTable->setSelectionMode(QAbstractItemView::SingleSelection);

    const QStringList headerLabels{"选择", "名称", "源路径", "备份到", "上次备份时间", };
    ui->backupTable->setColumnCount(headerLabels.length());
    ui->backupTable->setHorizontalHeaderLabels(headerLabels);
    ui->backupTable->setColumnWidth(0, 40);
    ui->backupTable->setColumnWidth(1, 200);
    ui->backupTable->setColumnWidth(2, 200);
    ui->backupTable->setColumnWidth(3, 200);
    ui->backupTable->setColumnWidth(4, 200);
    ui->backupTable->horizontalHeader()->setStretchLastSection(true);
    ui->backupTable->horizontalHeader()->setHighlightSections(false);
    ui->backupTable->verticalHeader()->setVisible(false);
}

void BTMainWindow::loadBackupConfigToTable()
{
    for(const BackupConfigObject &configObj : *m_backupConfigs){
        const int insertPosition = ui->backupTable->rowCount();
        ui->backupTable->insertRow(insertPosition);
        ui->backupTable->setRowHeight(insertPosition, BACKUP_TABLE_ROW_HEIGHT);
        ui->backupTable->setCellWidget(insertPosition, 0, getCheckBox());
        ui->backupTable->setItem(insertPosition, 1, new QTableWidgetItem(configObj.name));
        ui->backupTable->setItem(insertPosition, 2, new QTableWidgetItem(configObj.srcPath));
        ui->backupTable->setItem(insertPosition, 3, new QTableWidgetItem(configObj.dstPath));
    }
}

QWidget* BTMainWindow::getCheckBox()
{
    QWidget *retWidget = new QWidget(ui->backupTable);
    QHBoxLayout *hBox = new QHBoxLayout(retWidget);
    QVBoxLayout *vBox = new QVBoxLayout();
    QCheckBox *checkBox = new QCheckBox(retWidget);
    m_backupChBVector->append(checkBox);
    // TODO: Set QCheckBox Style
    connect(checkBox, &QCheckBox::stateChanged, this, &BTMainWindow::updateBackupConfigChecks, Qt::UniqueConnection);
    vBox->addStretch(1);
    vBox->addWidget(checkBox);
    vBox->addStretch(1);
    hBox->addStretch(1);
    hBox->addLayout(vBox);
    hBox->addStretch(1);
    return retWidget;
}

void BTMainWindow::startBackupProgress()
{
    int pos = 0;
    QString srcPath;
    QString dstPath;
    for(const QCheckBox *checkBox : *m_backupChBVector){
        if(checkBox->isChecked()){
            srcPath = ui->backupTable->item(pos, 2)->text();
            dstPath = ui->backupTable->item(pos, 3)->text();
            const QFileInfo sourceInfo(srcPath);
            const QFileInfo destinationInfo(dstPath);
            if(!sourceInfo.exists()){
                qCritical("source path not exists: %s", qUtf8Printable(srcPath));
                return;
            }
            if(!destinationInfo.exists() || !destinationInfo.isDir()){
                qCritical("destination path not exists: %s", qUtf8Printable(dstPath));
                return;
            }

            QThread *backupThread = new QThread();
            BackupProgressWorker *backupWorker = new BackupProgressWorker(srcPath, dstPath, CopyHelper::CopyMode::Force);

            connect(backupThread, &QThread::started, backupWorker, &BackupProgressWorker::startBackup);
            connect(backupWorker, &BackupProgressWorker::backupFinished, backupThread, &QThread::quit);
            connect(backupThread, &QThread::finished, backupThread, &QThread::deleteLater);
            connect(backupThread, &QThread::finished, backupWorker, &BackupProgressWorker::deleteLater);

            backupWorker->moveToThread(backupThread);
            backupThread->start();
        }
        pos++;
    }
}

void BTMainWindow::updateBackupConfigChecks(const int &state)
{
    state == 0 ? m_bakChBCheckedCount-- : m_bakChBCheckedCount++;
}

