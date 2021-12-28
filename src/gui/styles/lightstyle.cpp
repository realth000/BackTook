#include "lightstyle.h"

LightPushButtonStyle::LightPushButtonStyle()
    : PushButtonStyle(),
      normalColor("transparent"),
      hoverColor(235,235,235),
      pressedColor(51, 51, 51),
      disabledColor(40, 40, 40),
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
