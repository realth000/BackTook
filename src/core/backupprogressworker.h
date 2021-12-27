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

#ifndef BACKUPPROGRESSWORKER_H
#define BACKUPPROGRESSWORKER_H

#include <QtCore/QFileInfo>
#include <QtCore/QObject>
#include "utils/copyhelper.h"

class BackupProgressWorker : public QObject
{
    Q_OBJECT

public:
    BackupProgressWorker(const QString &srcPath, const QString &dstPath, const CopyMode &copyMode);

signals:
    void backupFinished();
    void fileBakcup(QString filePath, bool copyResult, QString errorMessage);

public slots:
    void startBackup();
    void terminateBackup();

private:
    QFileInfo m_srcFileInfo;
    QFileInfo m_dstFileInfo;
    CopyHelper m_copyHelper;
};

#endif // BACKUPPROGRESSWORKER_H
