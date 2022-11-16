#include "weatherinfo.h"

class WeatherDetail::Private{
public:
    Private(){}
    ~Private()
    {
        delete pix;
        pix = 0;
    }
    QString desc;
    QString icon;
    QPixmap *pix;
};

WeatherDetail::WeatherDetail() : d(new WeatherDetail::Private)
{}

WeatherDetail::~WeatherDetail()
{
    delete d;
    d = 0;
}

QString WeatherDetail::desc() const
{
    return d->desc;
}

void WeatherDetail::setDesc(const QString &desc)
{
    d->desc = desc;
}

QString WeatherDetail::icon() const
{
    return d->icon;
}

void WeatherDetail::setIcon(const QString &icon)
{
    d->icon = icon;
}

QPixmap* WeatherDetail::pix() const
{
    return d->pix;
}

void WeatherDetail::setPix(QPixmap *pix)
{
    d->pix = pix;
}

class WeatherInfo::Private{
public:
    Private(){}
    QString cityName;
    quint32 id;
    QDateTime dateTime;
    float temperature;
    float humidity;
    float pressure;
    QList<WeatherDetail*> details;
};

WeatherInfo::WeatherInfo() : d(new WeatherInfo::Private)
{}

WeatherInfo::~WeatherInfo()
{
    delete d;
    d = 0;
}

QString WeatherInfo::cityName() const
{
    return d->cityName;
}

void WeatherInfo::setCityName(const QString &cityName)
{
    d->cityName = cityName;
}

quint32 WeatherInfo::id() const
{
    return d->id;
}

void WeatherInfo::setId(quint32 id)
{
    d->id = id;
}

QDateTime WeatherInfo::dateTime() const
{
    return d->dateTime;
}

void WeatherInfo::setDateTime(const QDateTime &dateTime)
{
    d->dateTime = dateTime;
}

float WeatherInfo::temperature() const
{
    return d->temperature;
}

void WeatherInfo::setTemperature(float temperature)
{
    d->temperature = temperature;
}

float WeatherInfo::pressure() const
{
    return d->pressure;
}

void WeatherInfo::setPressure(float pressure)
{
    d->pressure = pressure;
}

float WeatherInfo::humidity() const
{
    return d->humidity;
}

void WeatherInfo::setHumidity(float humidity)
{
    d->humidity = humidity;
}

QList<WeatherDetail*> WeatherInfo::details() const
{
    return d->details;
}

void WeatherInfo::setDetails(const QList<WeatherDetail *> details)
{
    d->details = details;
}

QDebug operator <<(QDebug dbg, const WeatherDetail &w)
{
    dbg.nospace() << "("
                  << "Description: " << w.desc() << "; "
                  << "Icon: " << w.icon()
                  << ")";
    return dbg.space();
}

QDebug operator <<(QDebug dbg, const WeatherInfo &w)
{
    dbg.nospace() << "("
                  << "id: " << w.id() << "; "
                  << "City name: " << w.cityName() << "; "
                  << "Date time: " << w.dateTime().toString(Qt::DefaultLocaleLongDate) << ": " << endl
                  << "Temperature: " << w.temperature() << ", "
                  << "Pressure: " << w.pressure() << ", "
                  << "Humidity: " << w.humidity() << endl
                  << "Details: [";
    foreach (WeatherDetail *detail, w.details()) {
        dbg.nospace() << "( Description: " << detail->desc() << ", "
                      << "Icon: " << detail->icon() << "), ";
    }
    dbg.nospace() << "] )";
    return dbg.space();
}














