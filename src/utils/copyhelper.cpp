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

#include "copyhelper.h"
#include <QtCore/QFileInfo>

// test
#include <QThread>
#include <QDebug>

CopyHelper::CopyHelper(QObject *parent)
    : QObject(parent),
      m_stopCopy(false)
{

}

bool CopyHelper::copyFile(const QString &srcFilePath, const QString &dstFilePath, const CopyMode &copyMode)
{
#if 0
    QThread::sleep(1);
#endif
    if(m_stopCopy){
        return true;
    }
    bool ret = false;
    if(!QFile::exists(srcFilePath)){
        criticalLogger(QStringLiteral("source file not exists"), srcFilePath);
        return false;
    }
    if(copyMode == CopyMode::Force && QFile::exists(dstFilePath)){
        if(!QFile::remove(dstFilePath)){
            criticalLogger(QStringLiteral("source file can not overwrite"), srcFilePath);
            return false;
        }
    }
    ret = QFile::copy(srcFilePath, dstFilePath);
    if(ret){
        emit fileCopied(srcFilePath, true);
    }
    else{
        criticalLogger(QStringLiteral("failed during copy"), srcFilePath);
    }
    return ret;
}

void CopyHelper::copyDirectory(const QString &srcDirPath, const QString &dstDirPath, const CopyMode &copyMode)
{
    if(m_stopCopy){
        return;
    }
    QDir sourceDir(srcDirPath);
    if(!sourceDir.exists()){
        criticalLogger(QStringLiteral("source directory not exists"), srcDirPath);
    }
    const QFileInfoList sourceDirEntryList = sourceDir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
    for(const QFileInfo &sourceInfo : sourceDirEntryList){
        /*
         * TODO: now only handle on symbol link, file and directory,
         * other types should also be in concern.
         */
        if(sourceInfo.isSymLink()){
            if(!QFile::link(sourceInfo.absoluteFilePath(), dstDirPath + NATIVE_SEPARATOR + sourceInfo.fileName())){
                criticalLogger(QStringLiteral("failed to copy symbol link"), sourceInfo.fileName());
            }
        }
        else if(sourceInfo.isFile()){
            copyFile(sourceInfo.absoluteFilePath(), dstDirPath + NATIVE_SEPARATOR + sourceInfo.fileName(), copyMode);
        }
        else if(sourceInfo.isDir()){
            QDir dstDir(dstDirPath);
            if(dstDir.entryList(QDir::Files | QDir::NoDotAndDotDot).contains(sourceInfo.fileName())){
                dstDir.remove(sourceInfo.fileName());
            }
            if(!dstDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).contains(sourceInfo.fileName()) && !dstDir.mkdir(sourceInfo.fileName())){
                criticalLogger(QStringLiteral("create destination directory failed"), sourceInfo.fileName());
                continue;
            }
            copyDirectory(sourceInfo.absoluteFilePath(), dstDirPath + NATIVE_SEPARATOR + sourceInfo.fileName(), copyMode);
        }
    }
}

void CopyHelper::checkDirectoryInfo(const QString &directoryPath, qint64 &fileCount, qint64 &totalSize)
{
    if(directoryPath.isEmpty()){
        qCritical("CheckDirctoryInfo: empty directory path.");
        return;
    }
    fileCount = 0;
    totalSize = 0;
    QDirIterator it(directoryPath, QDir::Files | QDir::Dirs | QDir::Hidden, QDirIterator::Subdirectories);
    while(it.hasNext()){
        totalSize += it.fileInfo().size();
        if(it.fileInfo().isFile()){
            fileCount++;
        }
        it.next();
    }
    totalSize += it.fileInfo().size();
    if(it.fileInfo().isFile()){
        fileCount++;
    }
}

void CopyHelper::stopCopy()
{
    m_stopCopy = true;
}

void CopyHelper::criticalLogger(const QString &logBody, const QString &filePath)
{
    qCritical("Copy failed, %s: %s", qUtf8Printable(logBody), qUtf8Printable(filePath));
    emit fileCopied(filePath, false, logBody);
}

void CopyHelper::setCopyMode(const CopyMode &copyMode)
{
    m_copyMode = copyMode;
}
