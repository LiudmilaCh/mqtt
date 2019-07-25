/*
ЧЕРНОВИК ОБМЕНА ДАННЫМИ ДЛЯ ДАТЧИКОВ УМНОГО ДОМА ПО MQTT НА ОСНОВЕ ОТКРЫТОЙ БИБЛИОТЕКИ ДЛЯ QT
*/

#include <QGuiApplication>
#include <QWidgetList>
#include <QWidgetSet>
#include <QLabel>
#include <QtWidgets>
#include <QApplication>
#include <QQmlEngine>

#include <QQmlApplicationEngine>
#include <QObject>
#include <QTimer>
#include <QTime>

#include <QStringList>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>

#include <QPointer>
#include <QTimer>
#include <QDateTime>
#include <QHostInfo>
#include <QLoggingCategory>
#include <QMap>
#include <QMultiMap>

#include <QString>
//#include <qmqtt_client.h>
#include <QCoreApplication>
#include <QCommandLineParser>

#include <iostream>

#include "variables.h"
#include "info.h"
#include "qmqtt.h"


using QMQTT::Client;
using QMQTT::Will;
using QMQTT::Message;

using namespace std;

//extern QString data_out_data;
//extern QString data_from;

//class Message_data;
//key, value


//класс для получения данных

class Logger : public QObject {
  //  Q_OBJECT
    public:
      Q_PROPERTY(double data_message READ data_messsage1 WRITE showMqttData NOTIFY value_changed)
//Q_PROPERTY(double output READ WRITE NOTIFY)

//Logger(QObject* pobj): QObject(pobj), data_value(0))

  public:
//Logger(QObject* pobj = 0);
        Logger() : QObject() {

        }

        ~Logger() {

        }
        double data_value;
        QString topic_value;

  //        qDebug()<<"data_out_data = "<<data_out_data;
  //                      return data_out_data ;
  //      }

//QString data_out_data ;

    public slots:

Q_INVOKABLE
        void showMqttData(const QMQTT::Message &message) {


            //QString data(message.payload());
    //bool ok;
            data_out_data = ((message.payload()));//.toInt(&ok));
            bool ok;
            data_to_display = data_out_data.toDouble(&ok);
          //  bool ok;
            data_value = ((message.payload()).toDouble(&ok));
          //  co = (message.payload()).toDouble(&ok);
//---------------------------------------------------------------------------------
            //по значению топика определить значение сообщения с датчика по условию
//---------------------------------------------------------------------------------
            topic_value =  (message.topic());

            if (topic_value=="/devices/Humidity")
            {
                humidity_value = (message.payload());

            }
            else if (topic_value=="/devices/Illuminance") {
                illuminace_value = (message.payload());
            }
            
            else if (topic_value == "/devices/Temperature") {
                temperature_value = (message.payload());
            }
            
            else if(topic_value=="/devices/Current Motion"){
                motion_value = (message.payload());
            }
           
            else if(topic_value=="/devices/wb-msw-v3_111/controls/Air Quality (VOC)"){
              air_value  = (message.payload());
            }
          


            variable1 = 1;
            yes_data = true;
            data_received = 1;
// data_message1( data_to_display);


    qDebug()<<"thread show"<<QThread::currentThreadId();
    qDebug()<<"variable1"<<variable1;

    qDebug()<<"illuminace"<<data_out_data;
    qDebug()<<"illuminace double"<<data_to_display;
    qDebug()<<"topic name------>"<<topic_value;
    qDebug()<<"___________supply voltage--------"<<volt_value;
qDebug()<<"______humidity_____"<<humidity_value;
qDebug()<<"______illuminace_____"<<illuminace_value;
/*
QTimer *tmr;
tmr = new QTimer();
tmr->setInterval(5000);
*/
//qDebug()<<"data_from var"<<data_from;


emit value_changed(data_value);
//return data_message();
    //  return data_out_data;
        }

      Q_INVOKABLE double data_message1 () const
              {


           // n = data_to_display;

            // qDebug()<<"return data message"<<data_to_display;
                  //return  data_out_data ;
      //  unreacheble, add reading from stream->
                  // cout<<"to std string"<<data_out_data.toStdString()<<endl;
      //qDebug()<<""<<data_out_data;
      //qDebug()<<"data_from"<<data_from;
            return data_value;
              }

        Q_INVOKABLE QString data(){

            return "its_a_string";}



//-------------мой вывод  в строку данных------------



        void showSubscribed() {

            cout << "subscribed" << endl;

        }

        void showConnected() {

            cout << "connected!" << endl;

        }

        void showDisConnected() {

            cout << "disconnected!" << endl;

        }

signals:
  void value_changed(double){

}
};



class MyClient : public Client {

    public:

    MyClient(const QString & host, quint32 port) : Client(host, port) {

    }

    void setTopic(const QString & topic) {

        subTopic = topic;

    }

    void setQos(const QString & qos) {

        subQos = qos.toUInt();

    }

    public slots:

    void subscribeTo() {

        subscribe(subTopic, subQos);

    }



    private:

    QString subTopic;

    quint8 subQos;

};

//---------------------------------------------------------
//---------------------------------------------------------


int main (int argc, char ** argv)//(int argc, char *argv[])
{
QGuiApplication a(argc, argv);
//таймер
    QTimer *tmr;
    tmr = new QTimer();

    qmlRegisterType<Logger>("Message_data", 1, 0, "Logger");
qmlRegisterType<Give_data>("Give_data", 1, 0, "Give_data");
qmlRegisterType<Info>("Info",1,0, "Info");
//qmlRegisterType<MyClient>("Client",1,0, "Client");

//topic_name.append(t1);
//topic_name.append(t2);

//qmlRegisterType<Calculation>("com.myinc.Calculation", 1, 0, "Calculation");
/* изначальное объявление
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

      //  exchange();
      //  display_result ();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                    &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

*/



QMap<QString, int>::iterator i;
for (i = (sample.begin()); i!=sample.end(); i++)
//i = topic_n.begin();
qDebug()<<"sample names: "<<i.key();

//------------------------------------------------------
//--------------вывод имен топиков----------------------
QMap<QString, int>::iterator b;
  for (b = (topic_n.begin()); b!=topic_n.end(); b++)
    //  get_topic = b.key();
qDebug()<<"topic names:"<<b.key();
while (b != topic_n.end()) //get_topic =  b.key();
  //foreach (QString key, topic_n)
    //  qDebug()<<"value for each "<<key;
//i = topic_n.begin();


  qDebug()<<"get topic value: "<<b.value();
//------------------------------------------------------

  // data_to_display = 10;

  // engine.load(url);  //запуск окна программы из qml


qDebug()<<"thread1"<<QThread::currentThreadId();

      QString host = host_ext;

      quint32 port = 1883;

      QString qos = 0;

      QString topic  = topic_ext;

      cout << "using: host[" << host.toStdString() << "] port[" << port << "] qos[" << qos.toStdString() << "]" << endl;

      cout << "subscribe on topic[" << topic.toStdString() << "]" << endl;


//Message_data msg;
//Calculation data;
      Message message;
    //  Give_data msg;
      Logger s;



      MyClient c(host, port);

      c.setTopic(topic);

    //  c.setTopic(topic_new);

      c.setQos(qos);

//--------------------------------------------------------------------------
//слот-сигнал объектов qt для обмена данными по mqtt

      QObject::connect(&c, &MyClient::connected, &s, &Logger::showConnected);

      QObject::connect(&c, &MyClient::connected, &c, &MyClient::subscribeTo);

      QObject::connect(&c, &MyClient::disconnected, &s, &Logger::showDisConnected);

      QObject::connect(&c, &MyClient::subscribed, &s, &Logger::showSubscribed);

      QObject::connect(&c, &MyClient::received, &s, &Logger::showMqttData);
     
      QObject::connect(&a, &QCoreApplication::aboutToQuit, &c, &MyClient::disconnect);

      qDebug()<<"thread2"<<QThread::currentThreadId();


c.connect();


qDebug()<<"var1 = "<<variable1;

qDebug()<<"data received after"<<data_received;

qDebug()<<"data received from hardware"<<data_out_data;




QQmlApplicationEngine engine;
const QUrl url(QStringLiteral("qrc:/main.qml"));
QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                  &a, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
        QCoreApplication::exit(-1);
}, Qt::QueuedConnection);
engine.load(url);
      return a.exec();

}
