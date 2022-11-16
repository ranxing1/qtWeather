#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "weatherinfo.h"

#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QJsonParseError>
#include <QMessageBox>
#include <QMap>
#include <QPixmap>
#include <QPainter>

class MainWindow::Private{
public:
    Private(MainWindow *q) : mainWindow(q)
    {
        netWorker = NetWorker::getInstance();
    }

    void fetchWeather(const QString &cityName)
    {
        QNetworkReply *reply = netWorker->get(QString("http://api.openweathermap.org/data/2.5/weather"
                               "?q=%1&exclude=hourly,daily&lang=zh_cn"
                               "&appid=822c0d4500e71fa73485273f48708df0").arg(cityName));
//        replyMap.insert(reply,FetchWeatherInfo);

    }

    void fetchIcon(const QString &iconName)
    {
        //http://openweathermap.org/img/wn/10d.png
//        qDebug() << QString("http://openweathermap.org/img/wn/%1.png").arg(iconName);
        QNetworkReply *reply = netWorker->get(QString("http://openweathermap.org/img/wn/%1.png").arg(iconName));
//        replyMap.insert(reply, FetchWeatherIcon);
        //qDebug() << replyMap.value(reply);
    }



    NetWorker *netWorker;
    MainWindow *mainWindow;
//    QMap<QNetworkReply*,RemoteRequest> replyMap;
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , index(0)
    , ui(new Ui::MainWindow)
    , careTaker(new WeatherCaretaker)
    //, pixCareTaker(new PixCaretaker)
    , d(new MainWindow::Private(this))
    , request(FetchWeatherInfo)
{
    ui->setupUi(this);
    setWindowTitle(tr("Weather"));
    //选择城市
    ui->cityList->addItem(tr("Beijing"),QLatin1String("Beijing,cn"));
    ui->cityList->addItem(tr("Shanghai"), QLatin1String("Shanghai,cn"));
    ui->cityList->addItem(tr("Nanjing"), QLatin1String("Nanjing,cn"));
    ui->cityList->addItem(tr("Wuhan"),QLatin1String("Wuhan,cn"));
    ui->cityList->addItem(tr("Taiyuan"),QLatin1String("Taiyuan,cn"));
    ui->cityList->addItem(tr("Yuncheng"),QLatin1String("Yuncheng,cn"));
    ui->cityList->addItem(tr("Harbin"),QLatin1String("Harbin,cn"));
    ui->cityList->addItem(tr("Xian"),QLatin1String("Xian,cn"));

    //解析json数据
    connect(d->netWorker,&NetWorker::finished,[=](QNetworkReply *reply) mutable {
        switch (request)
        {
        case FetchWeatherInfo:
        {
            QJsonParseError error;
            QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(),&error);
            if(error.error == QJsonParseError::NoError)
            {
                if(!(jsonDocument.isNull() || jsonDocument.isEmpty()) && jsonDocument.isObject())
                {
                    QVariantMap data = jsonDocument.toVariant().toMap();

                    //创建并填充天气信息
                    WeatherInfo *weather = new WeatherInfo;
                    //设置城市名
                    weather->setCityName(data[QLatin1String("name")].toString());
                    QDateTime dateTime;
                    //设置时间
                    dateTime.setTime_t(data[QLatin1String("dt")].toLongLong());
                    weather->setDateTime(dateTime);
                    QVariantMap main = data[QLatin1String("main")].toMap();
                    //设置温度
                    weather->setTemperature(main[QLatin1String("temp")].toFloat());
                    //设置气压
                    weather->setPressure(main[QLatin1String("pressure")].toFloat());
                    //设置湿度
                    weather->setHumidity(main[QLatin1String("humidity")].toFloat());
                    QVariantList detailList = data[QLatin1String("weather")].toList();
                    QList<WeatherDetail*> details;
                    foreach (QVariant w, detailList) {
                        QVariantMap wm = w.toMap();
                        WeatherDetail *detail = new WeatherDetail;
                        detail->setDesc(wm[QLatin1String("description")].toString());
                        detail->setIcon(wm[QLatin1String("icon")].toString());
                        //qDebug() << detail->icon();
                        details.append(detail);
                    }
                    d->fetchIcon(details[0]->icon());
                    weather->setDetails(details);
                    //添加至备忘录
                    careTaker->addMemento(weather);
                    index = careTaker->size() - 1;
                    request = FetchWeatherIcon;
                    //显示信息
                    showWeather(index);
                }
            }
            else
            {
                QMessageBox::critical(this,tr("Error"),error.errorString());
            }
            break;
        }
        case FetchWeatherIcon:
        {
            QByteArray arr = reply->readAll();
            //qDebug() << arr.size();
            QPixmap *pixmap = new QPixmap;
            pixmap->loadFromData(arr);

            careTaker->getMemento(index)->details().at(0)->setPix(pixmap);
            request = FetchWeatherInfo;
            showPix(index);
            break;
        }
        }
        reply->deleteLater();
    });
    connect(ui->refresh,&QPushButton::clicked,[=](){
       d->fetchWeather(ui->cityList->itemData(ui->cityList->currentIndex()).toString());
    });
    //后退
    connect(ui->back,&QPushButton::clicked,[=](){
       if(index > 0)
       {
           index--;
           showWeather(index);
           showPix(index);
       }
       else{
           QMessageBox::critical(this,tr("Error"),tr("the first!"));
       }
    });

    connect(ui->next,&QPushButton::clicked,[=](){
       if(index < careTaker->size() - 1)
       {
           index++;
           showWeather(index);
           showPix(index);
       }
       else{
           QMessageBox::critical(this,tr("Error"),tr("no next!"));
       }
    });
}

void MainWindow::showWeather(int i)
{
    WeatherInfo *tmp = careTaker->getMemento(i);
    //城市名
    ui->curCityName->setText(tmp->cityName());
    //时间
    ui->curDateTime->setText(tmp->dateTime().toString(Qt::DefaultLocaleLongDate));
    //天气描述
    ui->curDesc->setText(tmp->details().at(0)->desc());
    //现在温度
    float x = (tmp->temperature() - 273.15);
    QString strt = QString::number(x);
    strt = strt.sprintf("%.2f",x);
    ui->curTem->setText(strt);
    //现在湿度
    QString strh = QString::number(tmp->humidity());
    strh += "%";
    ui->curHumidity->setText(strh);
    //现在气压
    QString strp = QString::number(tmp->pressure());
    ui->curPressure->setText(strp);
}

void MainWindow::showPix(int i)
{
    QPixmap map = *(careTaker->getMemento(i)->details().at(0)->pix());
    map = map.scaled(ui->curDescPix->size());
    ui->curDescPix->setPixmap(map);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete d;
    d = 0;
    delete careTaker;
    //delete pixCareTaker;
}

