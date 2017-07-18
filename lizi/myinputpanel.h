#ifndef MYINPUTPANEL_H
#define MYINPUTPANEL_H

#include <QWidget>
#include <QList>
#include <QChar>
#include <QString>
#include <QPoint>
#include "ui_myinputpanelform.h"
#include <QtSql>
#include "chnpanel.h"
class MyInputPannelContext;
class QDomDocument;
namespace Ui {
    class MyInputPanelForm;
}

class MyInputPanel : public QWidget
{
    Q_OBJECT
public:
    explicit MyInputPanel(MyInputPannelContext *ipc,QWidget *parent=0 );
    void numPro();
    void capsPro();
signals:
    void sendChar(QString ch);
    void sendInt(int key);

protected:
    bool event(QEvent *e);
    
private slots:
    void saveFocusWidget(QWidget *oldFocus, QWidget *newFocus);
    void btnClicked(QWidget *w);
    void btnChnClicked(QString w);
    void setEngChn();
    void transPy(const QString &text);
    void turnLeft();
    void turnRight();
private:
    Ui::MyInputPanelForm *inputform;
    QList<QPushButton *> btns;
    int btns_sz;
    QDomDocument *doc;
    int caps;
    int num;
    int xml_accu;
    QWidget *lastFocusedWidget;



    ChnPanel *chnpanel;//中文显示的列表
    //bool shift; /*indicate input capital letter or small letter*/
    bool num1;   /*indicate input character or number&punctuation*/
    bool chn;   /*indicate input English or Chinese*/
    //
    int pageCount;
    int currentPage;
    //
    QString chinese[128];
    QSqlTableModel *model;
    QSqlDatabase db;


    bool should_move;
    QPoint  mouse_pos;
    QPoint  widget_pos;



    //void setEngChn();
    void setMapping();
    void setConnect();
    void listChn();

    void loadDoc();
    void num_caps();
    QString getKeyBoardAttr();
    void setKBcharacter();
    void myMapping();
    void mousePressEvent(QEvent *e);
    void mouseReleaseEvent(QEvent *e);
    void mouseMoveEvent(QEvent *e);
    
};

#endif // MYINPUTPANEL_H
