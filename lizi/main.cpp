#include <QtGui/QApplication>
#include "ui_mainform.h"
#include "myinputpannelcontext.h"
#include <QTextCodec>
#include <QFont>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 以下部分解决中文乱码
     QTextCodec *codec = QTextCodec::codecForName("utf8"); //GBK gbk
     QTextCodec::setCodecForTr(codec);
     QTextCodec::setCodecForLocale(codec);
     QTextCodec::setCodecForCStrings(codec);

     QFont font("wenquanyi",12,QFont::Bold);
     a.setFont(font);
     // 以上部分解决中文乱码
    MyInputPannelContext *input=new MyInputPannelContext;
    a.setInputContext(input);
    QWidget w;
    Ui::MainForm form;
    form.setupUi(&w);
   // QApplication::setOverrideCursor(Qt::BlankCursor);
    w.show();
    

    return a.exec();
}
