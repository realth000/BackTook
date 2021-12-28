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
