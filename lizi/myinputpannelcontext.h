#ifndef MYINPUTPANNELCONTEXT_H
#define MYINPUTPANNELCONTEXT_H

#include <QInputContext>
class MyInputPanel;


class MyInputPannelContext : public QInputContext
{
    Q_OBJECT
public:
    explicit MyInputPannelContext(QObject *parent = 0);
    ~MyInputPannelContext();


    QString identifierName();
    QString language();

    bool isComposing() const;

    void reset();
    
    bool filterEvent(const QEvent* event);
signals:
    
public slots:
    void charSlot(QString character);
    void intSlot(int key);
private:
        MyInputPanel *inputpanel;
        void updatePosition();
        //void leftKey();
        void intKey(int Key);

};

#endif // MYINPUTPANNELCONTEXT_H
