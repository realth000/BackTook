#include "btaddbackupconfigdialog.h"
#include "ui_btaddbackupconfigdialog.h"

#include <QtWidgets/QFileDialog>
#include "utils/iconinstaller.h"
#include "utils/qssinstaller.h"

BTAddBackupConfigDialog::BTAddBackupConfigDialog(QWidget *parent, const bool &useLightStyle) :
      QDialog(parent),
      ui(new Ui::BTAddBackupConfigDialog),
      m_addedName(QString()),
      m_addedSrcPath(QString()),
      m_addedDstPath(QString()),
      m_useLightStyle(useLightStyle),
      m_darkPushButtonStyle(new DarkPushButtonStyle),
      m_lightPushButtonStyle(new LightPushButtonStyle)

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
    this->setMinimumSize(500, 250);
    ui->srcPathLineEdit->setReadOnly(true);
    ui->dstPathLineEdit->setReadOnly(true);
    ui->hintLabel->setVisible(false);
    if(m_useLightStyle){
        this->setStyleSheet(QssInstaller::installFromFile(":/stylesheet/btaddbackupconfigdialog_light.css"));
        IconInstaller::installPushButtonIcon(ui->okPushButton, ":/pic/yes2.png");
        IconInstaller::installPushButtonIcon(ui->cancelPushButton, ":/pic/cancel2.png");
        IconInstaller::installPushButtonIcon(ui->selectSrcPathPushButton, ":/pic/openfolder2.png");
        IconInstaller::installPushButtonIcon(ui->selectDstPathPushButton, ":/pic/openfolder2.png");
        ui->okPushButton->setStyle(m_lightPushButtonStyle);
        ui->cancelPushButton->setStyle(m_lightPushButtonStyle);
        ui->selectSrcPathPushButton->setStyle(m_lightPushButtonStyle);
        ui->selectDstPathPushButton->setStyle(m_lightPushButtonStyle);
    }
    else{
        this->setStyleSheet(QssInstaller::installFromFile(":/stylesheet/btaddbackupconfigdialog_dark.css"));
        IconInstaller::installPushButtonIcon(ui->okPushButton, ":/pic/yes.png");
        IconInstaller::installPushButtonIcon(ui->cancelPushButton, ":/pic/cancel.png");
        IconInstaller::installPushButtonIcon(ui->selectSrcPathPushButton, ":/pic/openfolder.png");
        IconInstaller::installPushButtonIcon(ui->selectDstPathPushButton, ":/pic/openfolder.png");
        ui->okPushButton->setStyle(m_darkPushButtonStyle);
        ui->cancelPushButton->setStyle(m_darkPushButtonStyle);
        ui->selectSrcPathPushButton->setStyle(m_darkPushButtonStyle);
        ui->selectDstPathPushButton->setStyle(m_darkPushButtonStyle);
    }
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
