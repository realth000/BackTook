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

#ifndef LIGHTSTYLE_H
#define LIGHTSTYLE_H

#include "basestyle.h"

class LightPushButtonStyle : public PushButtonStyle
{
public:
    LightPushButtonStyle();
    virtual void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;

private:
    const QColor normalColor;
    const QColor hoverColor;
    const QColor pressedColor;
    const QColor disabledColor;
    const QColor normalBorderColor;
    const QColor hoverBorderColor;
    const QColor pressedBorderColor;
    const QColor disabledBorderColor;
    const QColor textColor;
    const int borderWidth;
    const int iconOffset;
    const int iconWidth;
    const int iconHeight;
    const int testOffset;

};

#endif // LIGHTSTYLE_H
