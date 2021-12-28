#ifndef BTADDBACKUPCONFIGDIALOG_H
#define BTADDBACKUPCONFIGDIALOG_H

#include <QtWidgets/QDialog>
#include "gui/styles/darkstyle.h"
#include "gui/styles/lightstyle.h"

namespace Ui {
class BTAddBackupConfigDialog;
}

class BTAddBackupConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BTAddBackupConfigDialog(QWidget *parent = nullptr, const bool &useLightStyle = true);
    ~BTAddBackupConfigDialog();

signals:
    void getAddedBackupConfig(QString name, QString srcPath, QString dstPath);

private:
    Ui::BTAddBackupConfigDialog *ui;
    QString m_addedName;
    QString m_addedSrcPath;
    QString m_addedDstPath;
    bool m_useLightStyle;
    DarkPushButtonStyle *m_darkPushButtonStyle;
    LightPushButtonStyle *m_lightPushButtonStyle;
    void initUI();
    void initConnection();

private slots:
    void checkAddedConfig();
    void selectSrcPath();
    void selectDstPath();
};

#endif // BTADDBACKUPCONFIGDIALOG_H
