#include "basestyle.h"

#include <QtGui/QPainter>

PushButtonStyle::PushButtonStyle()
{

}

void PushButtonStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    Q_UNUSED(widget)
    if(element == CE_PushButton){
        if(const QStyleOptionButton *pb = qstyleoption_cast<const QStyleOptionButton *>(option)){
            QRect labelRect = pb->rect;
            // 抗锯齿
            painter->setRenderHint(QPainter::Antialiasing);
            if(pb->state & State_Enabled){
                // pressed
                if(pb->state & State_Sunken){
                    // 背景颜色
                    painter->save();
                    painter->setPen(QPen(pressedBorderColor, borderWidth));
                    painter->setBrush(pressedColor);
                    painter->drawRect(labelRect);
                    painter->restore();
                }
                // hover
                else if(pb->state & State_MouseOver){
                    // 背景颜色
                    painter->save();
                    painter->setPen(QPen(hoverBorderColor, borderWidth));
                    painter->setBrush(hoverColor);
                    painter->drawRect(labelRect);
                    painter->restore();
                }
                // 一般情况
                else{
                    // 背景颜色
                    painter->save();
                    painter->setPen(normalColor);
                    painter->setBrush(normalColor);
                    QPen emptyPen;
                    emptyPen.setWidth(0);
                    // 不要用painter->setCompositionMode(QPainter::CompositionMode_Clear);，会把border的setPen覆盖掉使之失效
                    //                    painter->setCompositionMode(QPainter::CompositionMode_Clear);
                    //                    painter->setBackgroundMode(Qt::TransparentMode);
                    painter->drawRect(labelRect);
                    painter->restore();
                }
                // 文字颜色
                painter->save();
#ifdef PUSHBUTTON_TEXT_BOLD
                QFont f = painter->font();
                f.setBold(true);
                painter->setFont(f);
#endif
                QTextOption optionS;
                optionS.setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
                painter->setPen(textColor);
                painter->drawText(labelRect.adjusted(iconOffset + iconWidth + testOffset,0,0,0), pb->text, optionS);
                painter->restore();
            }
            // diabled
            else{
                painter->save();
                painter->setPen(disabledBorderColor);
                painter->setBrush(disabledColor);
                painter->drawRect(labelRect);
                painter->restore();
                // disabled 文字颜色
                painter->save();
#ifdef PUSHBUTTON_TEXT_BOLD
                QFont f = painter->font();
                f.setBold(true);
                painter->setFont(f);
#endif
                QTextOption optionS;
                optionS.setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
                painter->setPen(Qt::gray);
                painter->drawText(labelRect.adjusted(iconOffset + iconWidth + testOffset,0,0,0), pb->text, optionS);
                painter->restore();


            }

            // 设置图标
            painter->save();
            QRect iconRect(labelRect.topLeft().x() + iconOffset, labelRect.topLeft().y() + 0.5*(labelRect.height() - iconHeight), iconWidth, iconHeight);
            painter->drawPixmap(iconRect, pb->icon.pixmap(QSize(iconWidth, iconHeight), QIcon::Mode::Normal));
            painter->restore();

            return;
        }
    }

    QProxyStyle::drawControl(element, option, painter, widget);

}
