#include "darkstyle.h"

DarkPushButtonStyle::DarkPushButtonStyle()
    : PushButtonStyle(),
      normalColor("transparent"),
      hoverColor(71, 71, 71),
      pressedColor(61, 61, 61),
      disabledColor(40, 40, 40),
      normalBorderColor("transparent"),
      hoverBorderColor(51, 85, 100),
      pressedBorderColor(51, 85, 100),
      disabledBorderColor(40, 40, 40),
      textColor(240, 255, 255),
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

void DarkPushButtonStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    PushButtonStyle::drawControl(element, option, painter, widget);
}
