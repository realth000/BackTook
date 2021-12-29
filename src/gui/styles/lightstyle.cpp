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

#include "lightstyle.h"

LightPushButtonStyle::LightPushButtonStyle()
    : PushButtonStyle(),
      normalColor("transparent"),
      hoverColor(235,235,235),
      pressedColor(210, 210, 210),
      disabledColor("transparent"),
      normalBorderColor("transparent"),
      hoverBorderColor(51, 85, 100),
      pressedBorderColor(51, 85, 100),
      disabledBorderColor(40, 40, 40),
      textColor(51, 51, 51),
      borderWidth(2),
      iconOffset(5),
      iconWidth(30),
      iconHeight(30),
      testOffset(5)
{
    PushButtonStyle::normalColor = normalColor;
    PushButtonStyle::hoverColor = hoverColor;
    PushButtonStyle::pressedColor = pressedColor;
    PushButtonStyle::disabledColor = disabledColor;
    PushButtonStyle::normalBorderColor = normalBorderColor;
    PushButtonStyle::hoverBorderColor = hoverBorderColor;
    PushButtonStyle::pressedBorderColor = pressedBorderColor;
    PushButtonStyle::disabledBorderColor = disabledBorderColor;
    PushButtonStyle::textColor = textColor;
    PushButtonStyle::borderWidth = borderWidth;
    PushButtonStyle::iconOffset = iconOffset;
    PushButtonStyle::iconWidth = iconWidth;
    PushButtonStyle::iconHeight = iconHeight;
    PushButtonStyle::testOffset = testOffset;
}

void LightPushButtonStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    PushButtonStyle::drawControl(element, option, painter, widget);
}
