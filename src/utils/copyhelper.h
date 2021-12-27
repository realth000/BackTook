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

#ifndef COPYHELPER_H
#define COPYHELPER_H

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QFile>

#ifndef NATIVE_SEPARATOR
#ifdef Q_OS_WINDOWS
#define NATIVE_SEPARATOR "\\"
#else
#define NATIVE_SEPARATOR "/"
#endif // #ifdef Q_OS_WINDOWS
#endif // #ifndef NATIVE_SEPARATOR

enum class CopyMode : int {
    Normal = 0,
    Force
};

class CopyHelper : public QObject
{
    Q_OBJECT

public:
    void setCopyMode(const CopyMode &copyMode);
    bool copyFile(const QString &srcFilePath, const QString &dstFilePath, const CopyMode &copyMode);
    void copyDirectory(const QString &srcDirPath, const QString &dstDirPath, const CopyMode &copyMode);
    static void checkDirectoryInfo(const QString &directoryPath, qint64 &fileCount, qint64 &totalSize);

signals:
    void fileCopied(QString filePath, bool copyResult, QString errorMessage = "");

private:
    CopyMode m_copyMode;

    void criticalLogger(const QString &logBody, const QString &filePath);
};

#endif // COPYHELPER_H
