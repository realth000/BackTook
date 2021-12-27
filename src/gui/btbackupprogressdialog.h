#ifndef BTBACKUPPROGRESSDIALOG_H
#define BTBACKUPPROGRESSDIALOG_H

#include <QtWidgets/QDialog>

namespace Ui {
class BTBackupProgressDialog;
}

class BTBackupProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BTBackupProgressDialog(QWidget *parent = nullptr);
    ~BTBackupProgressDialog();

signals:
    void terminateBackup();

public slots:
    void setHint(const QString &hint);
    void setFileCount(const qint64 &filecount);
    void updateBackupProgress(const QString &filePath, const bool &backupResult, const QString &errorMessage);
    void backupFinished();

private:
    Ui::BTBackupProgressDialog *ui;
    bool m_state;
    qint64 m_curremtFileCount;
    qint64 m_fileCount;

    void initUI();
    void initConnection();
    void updateSuccessLog(const QString &filePath);
    void updateFailedLog(const QString &filePath, const QString &errorMessage);
    void updateFinishedFileCount(const int &fileCount = 1);

private slots:
    void swithState();
    void terminate();

};

#endif // BTBACKUPPROGRESSDIALOG_H
