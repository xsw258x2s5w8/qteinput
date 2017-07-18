#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>//It's the case you have to pay attention
#include <QDebug>
#include <QSignalMapper>
#include <QFile>
#include <QMouseEvent>
#include <QMessageBox>
#include "myinputpanel.h"
#include "myinputpannelcontext.h"

MyInputPanel::MyInputPanel(MyInputPannelContext *ipc,QWidget *parent)
                  :QWidget(parent, Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool),
                  //: QWidget(parent, Qt::Tool | Qt::WindowStaysOnTopHint),
                    lastFocusedWidget(0)
{

    inputform=new Ui::MyInputPanelForm;
    inputform->setupUi(this);
    btns=findChildren<QPushButton *>();
    btns_sz=btns.size();
    xml_accu=0;
    chn=false;//一开始不为中文
    num1=false;
    chnpanel = new ChnPanel();//创建中文显示列表
    //chnpanel->setParent(this);
    chnpanel->setGeometry(100,400,300,40);
    chnpanel->setVisible(false);

    loadDoc();
    num_caps();
    setKBcharacter();

    //中英文切换按钮
    connect(this->inputform->pushButton_35,SIGNAL(clicked()),this,SLOT(setEngChn()));


    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
            this, SLOT(saveFocusWidget(QWidget*,QWidget*)));
    myMapping();
    connect(this,SIGNAL(sendChar(QString)),ipc,SLOT(charSlot(QString)));
    connect(this,SIGNAL(sendInt(int)),ipc,SLOT(intSlot(int)));

    connect(chnpanel->chnLineEdit,SIGNAL(textChanged(QString)),this,SLOT(transPy(QString)));//中文翻译
    connect(chnpanel->btnLeft,SIGNAL(clicked()),this,SLOT(turnLeft()));//上一页
    connect(chnpanel->btnRight,SIGNAL(clicked()),this,SLOT(turnRight()));//下一页



    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/opt/qt4.8.5/apps/data.db");
    //db.setDatabaseName("/home/test/data.db");
    if(!db.open())
    {
        QMessageBox::information(0,tr("无法打开数据库"),tr("需要SQLITE数据库的支持"));
    }
    qDebug()<<"数据库打开成功";

    //grDebug()<<"数据库打开成功";

    should_move=false;

}

void MyInputPanel::loadDoc()
{
    doc=new QDomDocument("keydoc");
    QFile file(":/keyboard.xml");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"xml file does not exist";
        return;
    }

    bool namespaceProcessing=false;
    QString *errorMsg = new QString();

    int errorLine=0;
    int errorColumn=0;

    QTextStream stream(&file);
    if(!doc->setContent(stream.readAll(),namespaceProcessing,errorMsg,&errorLine,&errorColumn))
    {
        qDebug()<<"can not set content";
        qDebug()<<"namespaceProcessing"<<namespaceProcessing;
        qDebug()<<"errormsg"<<errorMsg->toAscii();
        qDebug()<<"errorLine"<<errorLine;
        qDebug()<<"errorColomn"<<errorColumn;
        return;
    }
}

//--------------get num and caps keys' state--------------
void MyInputPanel::num_caps()
{
    bool OK;
    int caps_tmp,num_tmp;

    //---------------get keys' nr in XML----------------------------
    for(QDomNode n=doc->documentElement().firstChild();(!n.isNull());n=n.nextSibling())
    {
        xml_accu+=1;
        if(n.toElement().attribute("text").contains("CAPS"))
        {
            caps_tmp=n.toElement().attribute("nr").toInt(&OK);
            continue;
        }

        if(n.toElement().attribute("text").contains("NUM"))
        {
            num_tmp=n.toElement().attribute("nr").toInt(&OK);
            continue;
        }

    }


    for(int i=0;i<btns_sz;i++)
    {
        if(btns[i]->objectName().remove("pushButton_").toInt(&OK)==caps_tmp)
        {
            btns[i]->setCheckable(true);
            btns[i]->setChecked(false);
            caps=i;
            continue;

        }

        if(btns[i]->objectName().remove("pushButton_").toInt(&OK)==num_tmp)
        {
            btns[i]->setCheckable(true);
            btns[i]->setChecked(false);
            num=i;
            continue;
        }

    }

}

QString MyInputPanel::getKeyBoardAttr()
{
    QString str;
    if(btns[caps]->isChecked())
    {
        str="caps";
    }
    else if(btns[num]->isChecked())
    {
        str="num";
    }
    else
    {
        str="text";
    }
    return str;

}


void MyInputPanel::setKBcharacter()
{
    QDomElement root;
    bool OK;
    QFont font("",5);
    QString str=getKeyBoardAttr();
    //qDebug()<<"getKeyBoardAttr:"<<getKeyBoardAttr().toAscii();//test
    root=doc->documentElement();
    for(int i=0;i<btns_sz;i++)
    {
         for(QDomNode n=root.firstChild();(!n.isNull());n=n.nextSibling())
        {
             int button=btns[i]->objectName().remove("pushButton_").toInt(&OK);
             int xml=n.toElement().attribute("nr").toInt(&OK);
             if(button==xml)
             {
                 if(button==19)//'&'key display
                 {
                     if(str=="num")
                     {
                       btns[i]->setIconSize(btns[i]->size()*0.8);//--------------adjust
                        btns[i]->setIcon(QIcon(":/image/&.png"));
                        btns[i]->setText(n.toElement().attribute(str));
                        break;
                     }
                     else
                     {
                        btns[i]->setIcon(QIcon(""));
                        btns[i]->setText(n.toElement().attribute(str));
                        break;
                     }
                 }
                 else if(button<50)
                 {

                     btns[i]->setText(n.toElement().attribute(str));
                     //qDebug()<<"btns[i]->text()"<<btns[i]->text().toAscii();
                     //root.removeChild(n);
                     break;
                 }
                 else
                 {
                     switch(button)
                    {
                     case 50:
                         btns[i]->setIconSize(btns[i]->size());
                         //btns[i]->setIcon(QIcon(":/image/up.ico"));
                         btns[i]->setIcon(QIcon(":/img/up.png"));
                         btns[i]->setText("");
                         break;
                     case 51:
                         btns[i]->setIconSize(btns[i]->size());
                         //btns[i]->setIcon(QIcon(":/image/left.ico"));
                         btns[i]->setIcon(QIcon(":/img/left.png"));
                         btns[i]->setText("");
                         break;
                     case 52:
                         btns[i]->setIconSize(btns[i]->size());
                         //btns[i]->setIcon(QIcon(":/image/right.ico"));
                         btns[i]->setIcon(QIcon(":/img/right.png"));
                         btns[i]->setText("");
                         break;
                     case 53:
                         btns[i]->setIconSize(btns[i]->size());
                         //btns[i]->setIcon(QIcon(":/image/down.ico"));
                         btns[i]->setIcon(QIcon(":/img/down.png"));
                         btns[i]->setText("");
                         break;
                     case 54:
                     case 55:
                     case 56:
                     case 57:
                     case 58:
                         //QFont font("",5);
                         btns[i]->setFont(font);
                         btns[i]->setText(n.toElement().attribute("text"));
                         break;
                     default:
                         btns[i]->setText("test");

                     }

                 }

             }
        }
    }
}


void MyInputPanel::saveFocusWidget(QWidget *oldFocus, QWidget *newFocus)
{
    if (newFocus != 0 && !this->isAncestorOf(newFocus)) {
        lastFocusedWidget = newFocus;
       // qDebug()<<"lastFocusedWidget->objectName()"<<lastFocusedWidget->objectName();
    }
}

bool MyInputPanel::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::WindowActivate:
        if (lastFocusedWidget)
            lastFocusedWidget->activateWindow();
        break;
    case QEvent::MouseButtonPress:
        mousePressEvent(e);
        break;
    case QEvent::MouseButtonRelease:
        mouseReleaseEvent(e);
        break;
    case QEvent::MouseMove:
        mouseMoveEvent(e);
        break;
    default:
        break;
    }
    return QWidget::event(e);
}


void MyInputPanel::myMapping()
{
    QSignalMapper *myMapper1=new QSignalMapper(this);
    QSignalMapper *myMapper2=new QSignalMapper(this);
    for(int i=0;i<btns.size();i++)
    {
        myMapper1->setMapping(btns[i],btns[i]);
        connect(btns[i],SIGNAL(clicked()),myMapper1,SLOT(map()));
    }
    connect(myMapper1,SIGNAL(mapped(QWidget*)),this,SLOT(btnClicked(QWidget*)));

    for(int i=0;i<5;i++)
    {
        myMapper2->setMapping(chnpanel->chnLabel[i],chnpanel->chnLabel[i]);
        connect(chnpanel->chnLabel[i],SIGNAL(clicked(QString)),this,SLOT(btnChnClicked(QString)));
    }
   // connect(myMapper2,SIGNAL(mapped(ClickLabel*)),this,SLOT(btnChnClicked(ClickLabel*)));



}

void MyInputPanel::btnClicked(QWidget *w)
{
     QPushButton *btnp=static_cast<QPushButton *>(w);
     int btn;
     bool OK;
     btn=btnp->objectName().remove("pushButton_").toInt(&OK);
     if(btn<35)
     {
         QString ch=btnp->text();
         //qDebug()<<"ch"<<ch;
        //网lineedit添加字符
         if(chn&&!num1)
         {
            chnpanel->chnLineEdit->insert(ch);
         }
         else
         {
            emit sendChar(ch);
         }
     }
     else
     {
         emit sendInt(btn);
     }
}

void MyInputPanel::btnChnClicked(QString w)
{
     //QPushButton *btnp=static_cast<QPushButton *>(w);

        QString ch = w;
        qDebug()<<"ch="<<ch;
        //网lineedit添加字符
        emit sendChar(ch);

        //清空lineedit
        chnpanel->chnLineEdit->clear();



}

void MyInputPanel::capsPro()
{
    if(btns[caps]->isChecked())
    {
        btns[num]->setChecked(false);
    }
    setKBcharacter();
    update();
}




void MyInputPanel::numPro()
{
    if(btns[num]->isChecked())
    {
        btns[caps]->setChecked(false);
    }
    setKBcharacter();
    update();
}




void MyInputPanel::mousePressEvent (QEvent *e)
{
    QMouseEvent *event=static_cast<QMouseEvent *>(e);
    if (event->button()!=Qt::LeftButton) return;
    this->should_move = true;
    this->widget_pos = this->pos();
    this->mouse_pos = event->globalPos();

}
void MyInputPanel::mouseReleaseEvent(QEvent *e)
{
    QMouseEvent *event=static_cast<QMouseEvent *>(e);
    if (event->button()!=Qt::LeftButton) return;
    this->should_move = false;

}
void MyInputPanel::mouseMoveEvent ( QEvent *e)
{
    QMouseEvent *event=static_cast<QMouseEvent *>(e);
    if (this->should_move)
    {
        QPoint pos = event->globalPos();
        int x = pos.x()-this->mouse_pos.x();
        int y = pos.y()-this->mouse_pos.y();
        QWidget::move(this->widget_pos.x()+x,this->widget_pos.y()+y);
    }

}


//中英文切换函数
void MyInputPanel::setEngChn()
{
    qDebug()<<"中英文切换";

    //如果是数字按键就退出
    if(num1)
    {
        return;
    }
    chn=!chn;
    //shift=false;
    //kb->chnPanel->chnLineEdit->setText("");
    //中英文切换
    if(chn)
    {
        qDebug()<<"切换成中文";
        //如果是中文
        //kb->setGeometry(0,240,800,240);
        chnpanel->setVisible(true);
        //kb->keyBoard->setGeometry(0,60,800,180);
    //
        //kb->keyShift->setText(tr("CLR"));
        //kb->keyEngChn->setText(tr("ENG"));
    }
    else
    {
        qDebug()<<"切换成英文";
        //如果是英文
        //kb->setGeometry(0,300,800,180);
        chnpanel->setVisible(false);
        //kb->keyBoard->setGeometry(0,0,800,180);
    //
        //kb->keyShift->setText(tr("SFT"));
       // kb->keyEngChn->setText(tr("CHN"));
    }
    //setMapping();
}



void MyInputPanel::transPy(const QString &text)
{

    qDebug()<<"into transPy()";
    //model->setFilter("1");
    pageCount=0;
    currentPage=0;
    int i;
    //最多能够有128个中文单词
    for(i=0;i<128;i++)
    {
        chinese[i]="";
    }
    //
    if(text=="")
    {
        listChn();
    }
    else
    {
        QString py=text;
        py.prepend("'");
        py.append("%'");
        qDebug()<<py;


        QString select = "select * from pingyin where py like "+py+" limit 0,60";
        QSqlQuery query(db);
        query.prepare(select);
        int n=0;//初始化为0
        if(!query.exec())
        {
             qDebug()<<"查询出错！";
        }
        else
        {
            while(query.next())
            {
               chinese[n] = query.value(1).toString();
               qDebug()<<chinese[n];
               n++;
            }

        }



            /*
            model->setFilter("py=="+py);
            //model->select();
            int n=model->rowCount();
            qDebug()<<"count=";
            qDebug()<<n;
            for(i=0;i<n;i++)
            {
                chinese[i]=model->record(i).value(1).toString();
                qDebug()<<chinese[i];
            }
            */
        pageCount=n/5;
        if(n%5==0)
        {
            pageCount--;
        }
        listChn();
    }
}
//上一页
void MyInputPanel::turnLeft()
{
    if(currentPage==0)
    {
        return;
    }
    currentPage--;
    listChn();
}
//下一页
void MyInputPanel::turnRight()
{
    if(currentPage==pageCount)
    {
        return;
    }
    currentPage++;
    listChn();
}

//显示中文选择项，显示一排5个
void MyInputPanel::listChn()
{
    int i;
    for(i=0;i<5;i++)
    {
       chnpanel->chnLabel[i]->setText(chinese[5*currentPage+i]);
       //mapper->setMapping(chnpanel->chnLabel[i],chnpanel->chnLabel[i]->text());
    }
}



