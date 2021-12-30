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

#include "gui/btmainwindow.h"
#include <QtWidgets/QApplication>
#include <QtGui/QFontDatabase>

#ifdef Q_OS_WINDOWS
#include <QtGui/QFont>
#endif

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QFontDatabase appFontDatabase;
    appFontDatabase.addApplicationFont(":/pic/DejaVuSansMono-1.ttf");
    QFont appFont;
#ifdef Q_OS_WINDOWS
    appFont.setFamily("DejaVu Sans Mono,Microsoft Yahei");
#elif defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
    appFont.setFamily("Dejavu Sans Mono");
#endif
    a.setFont(appFont);
    BTMainWindow w;
    w.show();
    return a.exec();
}
