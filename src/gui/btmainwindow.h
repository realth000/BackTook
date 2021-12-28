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

#ifndef BTMAINWINDOW_H
#define BTMAINWINDOW_H

#include <QtCore/QDirIterator>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QMainWindow>

#include "core/btmaincontroller.h"
#include "defines.h"
#include "gui/styles/darkstyle.h"
#include "gui/styles/lightstyle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BTMainWindow; }
QT_END_NAMESPACE

class BTMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    BTMainWindow(QWidget *parent = nullptr);
    ~BTMainWindow();

signals:
    void sendBackupProgressHint(QString hint);
    void sendBackupProgressFileCount(qint64 fileCount);

public slots:
    void addBackupConfig(const QString &name, const QString &srcPath, const QString &dstPath);

private:
    Ui::BTMainWindow *ui;
    BTMainController *m_controller;
    BackupConfigDatas *m_backupConfigs;

    QWidget* getCheckBox();
    QVector<QCheckBox *> *m_backupChBVector;  // Store QCheckBox in TableWidget
    int m_bakChBCheckedCount;
    QString m_backupConfigSavePath;
    bool m_useLightStyle;
    DarkPushButtonStyle *m_darkPushbuttonStyle;
    LightPushButtonStyle *m_lightPushButtonStyle;

    void saveConfig();
    void loadConfig();
    void loadBackupConfig();
    void initConnection();
    void initUI();
    void initWindow();
    void initBackupTable();
    void loadBackupConfigToTable();
    void loadStyles();
    void addBackupConfigToDatas(const QString &name, const QString &srcPath, const QString &dstPath);
    void addBackupConfigToTable(const QString &name, const QString &srcPath, const QString &dstPath, const QString &lastBackupTime = "");
    void deleteBackupConfig(const int &pos);
    void updateBackupTime(const int &configIndex);

private slots:
    void startBackupProgress();
    void updateBackupConfigChecks(const int &state);
    void saveBackupConfig();
    void addConfig();
    void deleteConfig();

};
#endif // BTMAINWINDOW_H
