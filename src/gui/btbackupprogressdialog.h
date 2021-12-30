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

#ifndef BTBACKUPPROGRESSDIALOG_H
#define BTBACKUPPROGRESSDIALOG_H

#include <QtWidgets/QDialog>
#include <QtGui/QCloseEvent>
#include "gui/styles/darkstyle.h"
#include "gui/styles/lightstyle.h"

namespace Ui {
class BTBackupProgressDialog;
}

class BTBackupProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BTBackupProgressDialog(QWidget *parent = nullptr, const bool &useLightStyle = true);
    ~BTBackupProgressDialog();
    void setTaskCount(const int &taskCount);
    void appendLog(const QString &log);

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
    bool m_useLightStyle;
    DarkPushButtonStyle *m_darkPushButtonStyle;
    LightPushButtonStyle *m_lightPushButtonStyle;
    int m_taskCount;

    void initUI();
    void initConnection();
    void updateSuccessLog(const QString &filePath);
    void updateFailedLog(const QString &filePath, const QString &errorMessage);
    void updateFinishedFileCount(const int &fileCount = 1);
    void closeEvent(QCloseEvent *e) override;

private slots:
    void swithState();
    void terminate();

};

#endif // BTBACKUPPROGRESSDIALOG_H
