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

#ifndef BASESTYLES_H
#define BASESTYLES_H

#include <QtWidgets/QProxyStyle>
#include <QtWidgets/QStyleOptionButton>

class PushButtonStyle : public QProxyStyle
{
public:
    PushButtonStyle();
    virtual void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;

protected:
    QColor normalColor;
    QColor hoverColor;
    QColor pressedColor;
    QColor disabledColor;
    QColor normalBorderColor;
    QColor hoverBorderColor;
    QColor pressedBorderColor;
    QColor disabledBorderColor;
    QColor textColor;
    int borderWidth;
    int iconOffset;
    int iconWidth;
    int iconHeight;
    int testOffset;
};


#endif // BASESTYLES_H
