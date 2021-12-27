#include "btaddbackupconfigdialog.h"
#include "ui_btaddbackupconfigdialog.h"

#include <QtWidgets/QFileDialog>
#include "utils/qssinstaller.h"

BTAddBackupConfigDialog::BTAddBackupConfigDialog(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::BTAddBackupConfigDialog),
      m_addedName(QString()),
      m_addedSrcPath(QString()),
      m_addedDstPath(QString())

{
    ui->setupUi(this);
    initUI();
    initConnection();
}

BTAddBackupConfigDialog::~BTAddBackupConfigDialog()
{
    delete ui;
}

void BTAddBackupConfigDialog::initUI()
{
    this->setStyleSheet(QssInstaller::installFromFile(":/stylesheet/btaddbackupconfigdialog.css"));
    ui->srcPathLineEdit->setReadOnly(true);
    ui->dstPathLineEdit->setReadOnly(true);
    ui->hintLabel->setVisible(false);
}

void BTAddBackupConfigDialog::initConnection()
{
    connect(ui->nameLineEdit, &QLineEdit::textEdited, this, [this](const QString &name){this->m_addedName = name;});
    connect(ui->okPushButton, &QPushButton::clicked, this, &BTAddBackupConfigDialog::checkAddedConfig);
    connect(ui->selectSrcPathPushButton, &QPushButton::clicked, this, &BTAddBackupConfigDialog::selectSrcPath);
    connect(ui->selectDstPathPushButton, &QPushButton::clicked, this, &BTAddBackupConfigDialog::selectDstPath);
    connect(ui->cancelPushButton, &QPushButton::clicked, this, [this](){this->close();});
}

void BTAddBackupConfigDialog::checkAddedConfig()
{
    ui->hintLabel->setVisible(false);
    if(m_addedName.isEmpty() || m_addedSrcPath.isEmpty() || m_addedDstPath.isEmpty()){
        return;
    }
    if(m_addedSrcPath == m_addedDstPath){
        ui->hintLabel->setText("路径相同");
        ui->hintLabel->setVisible(true);
        return;
    }
    emit getAddedBackupConfig(m_addedName, m_addedSrcPath, m_addedDstPath);
    this->close();
}

void BTAddBackupConfigDialog::selectSrcPath()
{
    const QString path = QFileDialog::getExistingDirectory(this, "选择目录", QApplication::applicationDirPath());
    if(path.isEmpty()){
        return;
    }
    m_addedSrcPath = path;
    ui->srcPathLineEdit->setText(m_addedSrcPath);
}

void BTAddBackupConfigDialog::selectDstPath()
{
    const QString path = QFileDialog::getExistingDirectory(this, "选择目录", QApplication::applicationDirPath());
    if(path.isEmpty()){
        return;
    }
    m_addedDstPath = path;
    ui->dstPathLineEdit->setText(m_addedDstPath);
}
