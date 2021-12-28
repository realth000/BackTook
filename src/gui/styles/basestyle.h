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
