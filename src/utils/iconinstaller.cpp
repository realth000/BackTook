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

#include "iconinstaller.h"
#include <QPixmap>
#include <QIcon>

IconInstaller::IconInstaller()
{

}

void IconInstaller::installPushButtonIcon(QPushButton *pushButton, QString iconPath)
{
    if(pushButton == nullptr || iconPath.isEmpty()){
        return;
    }
    QIcon icon;
    const QPixmap pixmap = QPixmap(iconPath);
    if(pixmap.isNull()){
        return;
    }
    icon.addPixmap(pixmap, QIcon::Normal, QIcon::Off);
    pushButton->setIcon(icon);
}
