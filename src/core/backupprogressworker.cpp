#include "backupprogressworker.h"

// test
#include <QThread>
#include <QDebug>


BackupProgressWorker::BackupProgressWorker(const QString &srcPath, const QString &dstPath, const CopyHelper::CopyMode &copyMode)
    : m_srcFileInfo(srcPath),
      m_dstFileInfo(dstPath),
      m_copyMode(copyMode)
{

}

void BackupProgressWorker::startBackup()
{
    if(m_srcFileInfo.isFile()){
        // TODO: Save CopyMode in config
        CopyHelper::copyFile(m_srcFileInfo.absoluteFilePath(), m_dstFileInfo.absoluteFilePath(), CopyHelper::CopyMode::Force);
    }
    else if(m_srcFileInfo.isDir()){
        CopyHelper::copyDirectory(m_srcFileInfo.absoluteFilePath(), m_dstFileInfo.absoluteFilePath(), CopyHelper::CopyMode::Force);
    }

    // test
    qDebug() << "worker thread id:" << QThread::currentThreadId();

    emit backupFinished();
}
