#ifndef QSSINSTALLER_H
#define QSSINSTALLER_H
#include <QFile>
#include <QTextStream>
#include <QIODevice>

class QssInstaller
{
public:
    explicit QssInstaller();
    static QString installFromFile(QString qssFilePath);
};

#endif // QSSINSTALLER_H
