#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget *parent):QLabel(parent)
{
}
ClickLabel::ClickLabel(QString name,QWidget *parent):QLabel(parent)
{
    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    setText(name);
    status=false;
}

ClickLabel::~ClickLabel()
{
}

void ClickLabel::mousePressEvent(QMouseEvent *ev)
{
    if(!status)
    {
        status=true;
    }
}

void ClickLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(status)
    {
        emit clicked(this->text());
        status=false;
    }
}
