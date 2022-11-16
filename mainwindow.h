#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NetWorker.h"
#include "memento.h"
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int index;

    enum RemoteRequest {
        FetchWeatherInfo,
        FetchWeatherIcon
    };

private:
    void showWeather(int i);
    void showPix(int i);
    Ui::MainWindow *ui;

    WeatherCaretaker *careTaker;
    //PixCaretaker *pixCareTaker;

    RemoteRequest request;

    class Private;
    friend class Private;
    Private *d;
};
#endif // MAINWINDOW_H
