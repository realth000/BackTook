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

#include <QtWidgets/QMainWindow>
#include "core/btmaincontroller.h"
#include "defines.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BTMainWindow; }
QT_END_NAMESPACE

class BTMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    BTMainWindow(QWidget *parent = nullptr);
    ~BTMainWindow();
    void loadConfig();
    void initConnection();
    void initUI();

private:
    Ui::BTMainWindow *ui;
    BTMainController *m_controller;
    BackupConfigDatas *m_backupConfigs;

    void initBackupConfigTableWidget();

private slots:
    void startBackupProgress();

};
#endif // BTMAINWINDOW_H
