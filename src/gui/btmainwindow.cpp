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
#include "gui/btaddbackupconfigdialog.h"
#include "gui/btbackupprogressdialog.h"

#define WINDOW_MIN_WIDTH  1000
#define WINDOW_MIN_HEIGHT 700

#define BACKUP_TABLE_ROW_HEIGHT 35

BTMainWindow::BTMainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::BTMainWindow),
      m_controller(new BTMainController(this)),
      m_backupConfigs(new BackupConfigDatas),
      m_backupChBVector(new QVector<QCheckBox *>),
      m_bakChBCheckedCount(0),
      m_backupConfigSavePath(QApplication::applicationDirPath() + NATIVE_SEPARATOR + "backupConfig.json")
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

void BTMainWindow::addBackupConfig(const QString &name, const QString &srcPath, const QString &dstPath)
{
    addBackupConfigToDatas(name, srcPath, dstPath);
    addBackupConfigToTable(name ,srcPath, dstPath);
}

void BTMainWindow::addBackupConfigToTable(const QString &name, const QString &srcPath, const QString &dstPath, const QString &lastBackupTime)
{
    const int pos = ui->backupTable->rowCount();
    ui->backupTable->insertRow(pos);
    ui->backupTable->setRowHeight(pos, BACKUP_TABLE_ROW_HEIGHT);
    ui->backupTable->setCellWidget(pos, 0, getCheckBox());
    ui->backupTable->setItem(pos, 1, new QTableWidgetItem(name));
    ui->backupTable->setItem(pos, 2, new QTableWidgetItem(srcPath));
    ui->backupTable->setItem(pos, 3, new QTableWidgetItem(dstPath));
    ui->backupTable->setItem(pos, 4, new QTableWidgetItem(lastBackupTime));
}

void BTMainWindow::deleteBackupConfig(const int &pos)
{
    delete (*m_backupChBVector)[pos];
    m_backupChBVector->removeAt(pos);
    ui->backupTable->removeRow(pos);
    m_backupConfigs->removeAt(pos);
}

void BTMainWindow::updateBackupTime(const int &configIndex)
{
    const QString backupTime = QDateTime::currentDateTime().toString("yyyy.MM.dd-HH:mm:ss");
    QTableWidgetItem *item = ui->backupTable->item(configIndex, 4);
    if(item == nullptr){
        item = new QTableWidgetItem(backupTime);
        ui->backupTable->setItem(configIndex, 4, item);

    }
    item->setText(backupTime);
    (*m_backupConfigs)[configIndex].lastBackupTime = backupTime;
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
    JsonParser::saveBackupConfigJsonToFile(m_backupConfigSavePath, outVector);
#endif
    JsonParser::loadBackupConfigJsonFromFile(m_backupConfigSavePath, m_backupConfigs);
    qDebug() << "load result:" << JsonParser::backupConfigToString(*m_backupConfigs);
}

void BTMainWindow::initConnection()
{
    // startBackupPushButton
    connect(ui->startBackupPushButton, &QPushButton::clicked, this, &BTMainWindow::startBackupProgress);
    connect(ui->saveBackupPushButton, &QPushButton::clicked, this, &BTMainWindow::saveConfig);
    connect(ui->addBackupPushButton, &QPushButton::clicked, this, &BTMainWindow::addConfig);
    connect(ui->deleteBackupPushButton, &QPushButton::clicked, this, &BTMainWindow::deleteConfig);
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
        addBackupConfigToTable(configObj.name, configObj.srcPath, configObj.dstPath, configObj.lastBackupTime);
    }
}

void BTMainWindow::addBackupConfigToDatas(const QString &name, const QString &srcPath, const QString &dstPath)
{
    BackupConfigObject obj;
    obj.id = QString("-1");
    obj.name = name;
    obj.lastBackupTime = "";
    obj.srcPath = srcPath;
    obj.dstPath = dstPath;
    m_backupConfigs->append(obj);
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
    bool backupCanceled = false;
    int pos = 0;
    QString srcPath;
    QString dstPath;
    qint64 fileCount = 0;
    qint64 totalSize = 0;
    BTBackupProgressDialog *progressDialog = new BTBackupProgressDialog(this);
    connect(this, &BTMainWindow::sendBackupProgressHint, progressDialog, &BTBackupProgressDialog::setHint);
    connect(this, &BTMainWindow::sendBackupProgressFileCount, progressDialog, &BTBackupProgressDialog::setFileCount);
    connect(progressDialog, &BTBackupProgressDialog::terminateBackup, this, [&backupCanceled](){backupCanceled = true;});
    progressDialog->show();

    emit sendBackupProgressHint("计算文件中");
    int taskCount = 0;
    for(const QCheckBox *checkBox : *m_backupChBVector){
        if(checkBox->isChecked()){
            CopyHelper::checkDirectoryInfo(ui->backupTable->item(pos, 2)->text(), fileCount, totalSize);
            taskCount++;
         }
        pos++;
    }
    emit sendBackupProgressFileCount(fileCount);

    emit sendBackupProgressHint("备份中");
    pos = 0;
    for(const QCheckBox *checkBox : *m_backupChBVector){
        if(checkBox->isChecked()){
            if(backupCanceled){
                return;
            }
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
            BackupProgressWorker *backupWorker = new BackupProgressWorker(srcPath, dstPath, CopyMode::Force);
            connect(progressDialog, &BTBackupProgressDialog::terminateBackup, backupThread, &QThread::quit);
            connect(progressDialog, &BTBackupProgressDialog::terminateBackup, backupWorker, &BackupProgressWorker::terminateBackup, Qt::DirectConnection);

            connect(backupThread, &QThread::started, backupWorker, &BackupProgressWorker::startBackup);
            connect(backupWorker, &BackupProgressWorker::backupFinished, backupThread, &QThread::quit);
            connect(backupThread, &QThread::finished, backupThread, &QThread::deleteLater);
            connect(backupThread, &QThread::finished, backupWorker, &BackupProgressWorker::deleteLater);

            connect(backupWorker, &BackupProgressWorker::fileBakcup, progressDialog, &BTBackupProgressDialog::updateBackupProgress, Qt::BlockingQueuedConnection);
            connect(backupWorker, &BackupProgressWorker::backupFinished, this,
                    [&taskCount, progressDialog, pos, this]()
                    {
                        updateBackupTime(pos);
                        taskCount--;
                        if(taskCount == 0){
                            progressDialog->backupFinished();
                        }
                    });

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

void BTMainWindow::saveConfig()
{
    JsonParser::saveBackupConfigJsonToFile(m_backupConfigSavePath, *m_backupConfigs) ? qInfo("Save config success") : qInfo("Save config failed");
}

void BTMainWindow::addConfig()
{
    BTAddBackupConfigDialog *addConfigDialog = new BTAddBackupConfigDialog(this);
    connect(addConfigDialog, &BTAddBackupConfigDialog::getAddedBackupConfig, this, &BTMainWindow::addBackupConfig);
    addConfigDialog->exec();
}

void BTMainWindow::deleteConfig()
{
    // TODO: Freeze before delete.
    for(int i = 0; i < m_backupChBVector->length(); ++i){
        if((*m_backupChBVector)[i]->isChecked()){
            deleteBackupConfig(i);
        }
    }
    // TODO: Unfreeze after delete.
}
