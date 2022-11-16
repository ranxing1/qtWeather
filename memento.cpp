#include "memento.h"
#include <QDebug>

WeatherCaretaker::WeatherCaretaker()
{
    this->mementoList = new QLinkedList<WeatherInfo*>();
}

WeatherCaretaker::~WeatherCaretaker()
{
//    QLinkedList<WeatherInfo>::iterator i;
    for(auto i = mementoList->begin();i != mementoList->end();++i)
    {
        delete *i;
    }
    delete mementoList;
}

void WeatherCaretaker::addMemento(WeatherInfo* memento)
{
    if(mementoList->size() >= 5)
    {
        WeatherInfo* tmp = mementoList->front();
        mementoList->pop_front();
        delete tmp;
    }
    mementoList->append(memento);
}

WeatherInfo* WeatherCaretaker::getMemento(int i)
{
    return *(mementoList->begin() + i);
}

int WeatherCaretaker::size()
{
    return mementoList->size();
}



//PixCaretaker::PixCaretaker()
//{
//    this->mementoList = new QLinkedList<QPixmap*>;
//}

//PixCaretaker::~PixCaretaker()
//{
//    for(auto i = mementoList->begin();i != mementoList->end();++i)
//    {
//        delete *i;
//    }
//    delete mementoList;
//}

//void PixCaretaker::addMemento(QPixmap *memento)
//{
//    if(mementoList->size() >= 5)
//    {
//        QPixmap* tmp = mementoList->front();
//        mementoList->pop_front();
//        delete tmp;
//    }
//    mementoList->append(memento);
//}

//QPixmap* PixCaretaker::getMemento(int i)
//{
//    return *(mementoList->begin() + i);
//}

//int PixCaretaker::size()
//{
//    return mementoList->size();
//}
