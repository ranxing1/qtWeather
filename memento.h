#ifndef MEMENTO_H
#define MEMENTO_H

#include "weatherinfo.h"
#include <QLinkedList>
#include <QPixmap>

class WeatherCaretaker{
public:
    WeatherCaretaker();
    ~WeatherCaretaker();
    void addMemento(WeatherInfo *memento);
    WeatherInfo* getMemento(int i);
    int size();

private:
    QLinkedList<WeatherInfo*> *mementoList;
};

class PixCaretaker{
public:
    PixCaretaker();
    ~PixCaretaker();
    void addMemento(QPixmap *memento);
    QPixmap* getMemento(int i);
    int size();

private:
    QLinkedList<QPixmap*> *mementoList;
};


#endif // MEMENTO_H
