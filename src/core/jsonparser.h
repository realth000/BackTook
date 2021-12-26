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

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "defines.h"

#define BACKUP_JSON_KEY_ID   "Id"
#define BACKUP_JSON_KEY_NAME "Name"
#define BACKUP_JSON_KEY_TIME "LastBackupTime"
#define BACKUP_JSON_KEY_SRC  "SourcePath"
#define BACKUP_JSON_KEY_DST  "DestinationPath"

class JsonParser
{
public:
    static bool saveBackupConfigJsonToFile(const QString &filePath, const BackupConfigDatas &backupConfigJson);
    static bool saveBackupConfigJsonToFile(QFile &file, const BackupConfigDatas &backupConfigJson);
    static void loadBackupConfigJsonFromFile(const QString &filePath, BackupConfigDatas *backupConfigJson);
    static QString backupConfigToString(const BackupConfigDatas &backupConfigJson);
};

#endif // JSONPARSER_H
