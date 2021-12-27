#ifndef BTADDBACKUPCONFIGDIALOG_H
#define BTADDBACKUPCONFIGDIALOG_H

#include <QtWidgets/QDialog>

namespace Ui {
class BTAddBackupConfigDialog;
}

class BTAddBackupConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BTAddBackupConfigDialog(QWidget *parent = nullptr);
    ~BTAddBackupConfigDialog();

signals:
    void getAddedBackupConfig(QString name, QString srcPath, QString dstPath);

private:
    Ui::BTAddBackupConfigDialog *ui;
    QString m_addedName;
    QString m_addedSrcPath;
    QString m_addedDstPath;
    void initUI();
    void initConnection();

private slots:
    void checkAddedConfig();
    void selectSrcPath();
    void selectDstPath();
};

#endif // BTADDBACKUPCONFIGDIALOG_H
