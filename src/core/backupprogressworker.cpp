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

#include "backupprogressworker.h"

// test
#include <QThread>
#include <QDebug>


BackupProgressWorker::BackupProgressWorker(const QString &srcPath, const QString &dstPath, const CopyMode &copyMode)
    : m_srcFileInfo(srcPath),
      m_dstFileInfo(dstPath)
{
    m_copyHelper.setCopyMode(copyMode);
    connect(&m_copyHelper, &CopyHelper::fileCopied, this, &BackupProgressWorker::fileBakcup);
}

void BackupProgressWorker::startBackup()
{
    if(m_srcFileInfo.isFile()){
        // TODO: Save CopyMode in config
        m_copyHelper.copyFile(m_srcFileInfo.absoluteFilePath(), m_dstFileInfo.absoluteFilePath(), CopyMode::Force);
    }
    else if(m_srcFileInfo.isDir()){
        m_copyHelper.copyDirectory(m_srcFileInfo.absoluteFilePath(), m_dstFileInfo.absoluteFilePath(), CopyMode::Force);
    }
    emit backupFinished();
}

void BackupProgressWorker::terminateBackup()
{
    m_copyHelper.stopCopy();
}
