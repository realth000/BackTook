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
#include "core/backupprogressworker.h"
#include "core/jsonparser.h"

BTMainWindow::BTMainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::BTMainWindow),
      m_controller(new BTMainController(this)),
      m_backupConfigs(new BackupConfigDatas)
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
    initBackupConfigTableWidget();

}

void BTMainWindow::initBackupConfigTableWidget()
{
    const int backupConfigCount = m_backupConfigs->length();
    if(backupConfigCount <= 0){
        return;
    }
    const QStringList headerLabels{"选择", "名称", "源路径", "备份到", "上次备份时间"};
    ui->backupConfigTableWidget->setRowCount(backupConfigCount);
    ui->backupConfigTableWidget->setColumnCount(headerLabels.length());
    ui->backupConfigTableWidget->setColumnWidth(0, 40);
    ui->backupConfigTableWidget->setColumnWidth(1, 80);
    ui->backupConfigTableWidget->setColumnWidth(2, 80);
    ui->backupConfigTableWidget->setColumnWidth(3, 80);
    ui->backupConfigTableWidget->setColumnWidth(4, 80);
    ui->backupConfigTableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->backupConfigTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->backupConfigTableWidget->horizontalHeader()->setHighlightSections(false);
    ui->backupConfigTableWidget->verticalHeader()->setVisible(false);
}

void BTMainWindow::startBackupProgress()
{
    // Test:
    QString srcPath = "C:/QtProjects/0/test";
    QString dstPath = "C:/QtProjects/0/testdst";

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

