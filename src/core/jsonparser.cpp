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

#include "jsonparser.h"
#include <QtCore/QDateTime>
#include <QtCore/QJsonParseError>

bool JsonParser::saveBackupConfigJsonToFile(const QString &filePath, const BackupConfigDatas &backupConfigJson)
{
    QFile file(filePath);
    return saveBackupConfigJsonToFile(file, backupConfigJson);
}

bool JsonParser::saveBackupConfigJsonToFile(QFile &file, const BackupConfigDatas &backupConfigJson)
{
    if(!file.open(QIODevice::WriteOnly)){
        qCritical("JsonParser: json file cannot open: %s", qUtf8Printable(file.fileName()));
        return false;
    }
    QJsonDocument configJsonDoc;
    QJsonObject configJsonObject;
    int id = 0;
    for(const BackupConfigObject &singleConfig : backupConfigJson){
        QJsonObject configJsonSingleObject;
        configJsonSingleObject.insert(QStringLiteral(BACKUP_JSON_KEY_ID), id);
        configJsonSingleObject.insert(QStringLiteral(BACKUP_JSON_KEY_NAME), singleConfig.name);
        configJsonSingleObject.insert(QStringLiteral(BACKUP_JSON_KEY_TIME), singleConfig.lastBackupTime);
        configJsonSingleObject.insert(QStringLiteral(BACKUP_JSON_KEY_SRC), singleConfig.srcPath);
        configJsonSingleObject.insert(QStringLiteral(BACKUP_JSON_KEY_DST), singleConfig.dstPath);
        configJsonObject.insert(QString::number(id), configJsonSingleObject);
        id++;
    }
    configJsonDoc.setObject(configJsonObject);
    const QByteArray jsonData = configJsonDoc.toJson();
    const bool ret = file.write(jsonData) == jsonData.length() ? true : false;
    file.close();
    return ret;
}

void JsonParser::loadBackupConfigJsonFromFile(const QString &filePath, BackupConfigDatas *backupConfigJson)
{
    QFile configFile(filePath);
    if(!configFile.exists()){
        qCritical("JsonParser: json file not exists: %s", qUtf8Printable(filePath));
        return;
    }

    if(!configFile.open(QIODevice::ReadOnly)){
        qCritical("JsonParser: json file cannot open: %s", qUtf8Printable(filePath));
        return;
    }
    QJsonDocument configJsonDoc;
    QJsonObject configJsonObject;
    QJsonParseError configJsonError;
    QString readStr = configFile.readAll();
    configJsonDoc = QJsonDocument::fromJson(readStr.toUtf8(), &configJsonError);
    if(configJsonError.error != QJsonParseError::NoError){
        qCritical("JsonParser: json file parse error: %s, ", qUtf8Printable(filePath), qUtf8Printable(configJsonError.errorString()));
        return;
    }
    configJsonObject = configJsonDoc.object();
    const QStringList dataIdLists = configJsonObject.keys();
    for(const QString &dataId : dataIdLists){
        const QJsonObject configJsonSingleObject = configJsonObject.value(dataId).toObject();
        BackupConfigObject obj;
        obj.id = configJsonSingleObject.value(QStringLiteral(BACKUP_JSON_KEY_ID)).toString();
        obj.name = configJsonSingleObject.value(QStringLiteral(BACKUP_JSON_KEY_NAME)).toString();
        obj.lastBackupTime = configJsonSingleObject.value(QStringLiteral(BACKUP_JSON_KEY_TIME)).toString();
        obj.srcPath = configJsonSingleObject.value(QStringLiteral("SourcePath")).toString();
        obj.dstPath = configJsonSingleObject.value(QStringLiteral(BACKUP_JSON_KEY_DST)).toString();
        backupConfigJson->append(obj);
    }
    configFile.close();
}

QString JsonParser::backupConfigToString(const BackupConfigDatas &backupConfigJson)
{
    QString ret;
    for(const BackupConfigObject &backupObj : backupConfigJson){
        ret += backupObj.id       + "," +
               backupObj.name     + "," +
               backupObj.srcPath  + "," +
               backupObj.dstPath  + "," +
               backupObj.lastBackupTime;
#ifdef Q_OS_WINDOWS
        ret += "\r\n";
#else
        ret += "\n";
#endif
    }
    return ret;
}
