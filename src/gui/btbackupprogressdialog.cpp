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

#include "btbackupprogressdialog.h"
#include "ui_btbackupprogressdialog.h"

#include <QtCore/QDebug>
#include "utils/iconinstaller.h"
#include "utils/qssinstaller.h"

BTBackupProgressDialog::BTBackupProgressDialog(QWidget *parent, const bool &useLightStyle) :
      QDialog(parent),
      ui(new Ui::BTBackupProgressDialog),
      m_state(false),
      m_curremtFileCount(0),
      m_fileCount(0),
      m_useLightStyle(useLightStyle),
      m_darkPushButtonStyle(new DarkPushButtonStyle),
      m_lightPushButtonStyle(new LightPushButtonStyle),
      m_taskCount(0)
{
    ui->setupUi(this);
    initUI();
    initConnection();
}

BTBackupProgressDialog::~BTBackupProgressDialog()
{
    delete ui;
    delete m_darkPushButtonStyle;
    delete m_lightPushButtonStyle;
}

void BTBackupProgressDialog::setTaskCount(const int &taskCount)
{
    m_taskCount = taskCount;
}

void BTBackupProgressDialog::setHint(const QString &hint)
{
    ui->hintLabel->setText(hint);
}

void BTBackupProgressDialog::setFileCount(const qint64 &fileCount)
{
    m_fileCount = fileCount;
    ui->countLabel->setText("0/" + QString::number(m_fileCount));
}

void BTBackupProgressDialog::updateBackupProgress(const QString &filePath, const bool &backupResult, const QString &errorMessage)
{
    ui->currentFileLabel->setText(filePath);
    updateFinishedFileCount();
    backupResult ? updateSuccessLog(filePath) : updateFailedLog(filePath, errorMessage);
}

void BTBackupProgressDialog::backupFinished()
{
    m_taskCount--;
    if(m_taskCount > 0 ){
        return;
    }
    ui->hintLabel->setText("备份完成");
    ui->logTextEdit->append("备份完成");
    ui->terminatePushButton->setEnabled(false);
}

void BTBackupProgressDialog::initUI()
{
    setFixedWidth(900);
    setMinimumHeight(600);
    setWindowFlags(windowFlags() & static_cast<Qt::WindowType>(~Qt::WindowContextHelpButtonHint));
    setWindowTitle("备份");
    ui->logTextEdit->setReadOnly(true);

    // TODO: Pause and continue backup
    ui->swithStatePushButton->setVisible(false);
    if(m_useLightStyle){
        this->setStyleSheet(QssInstaller::installFromFile(":/stylesheet/btbackupprogressdialog_light.css"));
        IconInstaller::installPushButtonIcon(ui->terminatePushButton, ":/pic/cancel2.png");
        ui->terminatePushButton->setStyle(m_lightPushButtonStyle);
    }
    else{
        this->setStyleSheet(QssInstaller::installFromFile(":/stylesheet/btbackupprogressdialog_dark.css"));
        IconInstaller::installPushButtonIcon(ui->terminatePushButton, ":/pic/cancel.png");
        ui->terminatePushButton->setStyle(m_darkPushButtonStyle);
    }
}

void BTBackupProgressDialog::initConnection()
{
    connect(ui->swithStatePushButton, &QPushButton::clicked, this, &BTBackupProgressDialog::swithState);
    connect(ui->terminatePushButton, &QPushButton::clicked, this, &BTBackupProgressDialog::terminate);
}

void BTBackupProgressDialog::updateSuccessLog(const QString &filePath)
{
    ui->logTextEdit->append(QString("Success: %1").arg(filePath));
}

void BTBackupProgressDialog::updateFailedLog(const QString &filePath, const QString &errorMessage)
{
    ui->logTextEdit->append(QString("Failed: %1(%2)").arg(filePath, errorMessage));
}

void BTBackupProgressDialog::updateFinishedFileCount(const int &fileCount)
{
    m_curremtFileCount += fileCount;
    ui->countLabel->setText(QString("%1/%2").arg(QString::number(m_curremtFileCount), QString::number(m_fileCount)));
    ui->backupProgressBar->setValue(100*m_curremtFileCount/m_fileCount);
}

void BTBackupProgressDialog::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e)
    if(m_taskCount > 0){
        emit terminateBackup();
    }
}

// TODO: Pause and continue.
void BTBackupProgressDialog::swithState()
{

}

// TODO: Stop and cancel.
void BTBackupProgressDialog::terminate()
{
    emit terminateBackup();
    m_taskCount = 0;
    backupFinished();
    ui->hintLabel->setText("已停止");
    ui->logTextEdit->append("已停止");
}
