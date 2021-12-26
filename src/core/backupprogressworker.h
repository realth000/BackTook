#ifndef BACKUPPROGRESSWORKER_H
#define BACKUPPROGRESSWORKER_H

#include <QtCore/QFileInfo>
#include <QtCore/QObject>
#include "utils/copyhelper.h"

class BackupProgressWorker : public QObject
{
    Q_OBJECT

public:
    BackupProgressWorker(const QString &srcPath, const QString &dstPath, const CopyHelper::CopyMode &copyMode);

signals:
    void backupFinished();

public slots:
    void startBackup();

private:
    QFileInfo m_srcFileInfo;
    QFileInfo m_dstFileInfo;
    CopyHelper::CopyMode m_copyMode;
};

#endif // BACKUPPROGRESSWORKER_H
