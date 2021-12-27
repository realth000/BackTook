#include "btbackupprogressdialog.h"
#include "ui_btbackupprogressdialog.h"
#include <QtCore/QDebug>

BTBackupProgressDialog::BTBackupProgressDialog(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::BTBackupProgressDialog),
      m_state(false),
      m_curremtFileCount(0),
      m_fileCount(0)
{
    ui->setupUi(this);
    initUI();
    initConnection();
}

BTBackupProgressDialog::~BTBackupProgressDialog()
{
    delete ui;
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
    ui->hintLabel->setText("备份完成");
    ui->logTextEdit->append("备份完成");
}

void BTBackupProgressDialog::initUI()
{
    this->setFixedWidth(900);
    this->setMinimumHeight(600);
    ui->logTextEdit->setReadOnly(true);
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

// TODO: Pause and continue.
void BTBackupProgressDialog::swithState()
{

}

// TODO: Stop and cancel.
void BTBackupProgressDialog::terminate()
{
    emit terminateBackup();
    ui->hintLabel->setText("已停止");
    ui->logTextEdit->append("已停止");
}
