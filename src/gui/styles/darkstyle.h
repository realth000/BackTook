#ifndef DARKSTYLE_H
#define DARKSTYLE_H

#include "basestyle.h"
class DarkPushButtonStyle : public PushButtonStyle
{
public:
    DarkPushButtonStyle();
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

#endif // DARKSTYLE_H
