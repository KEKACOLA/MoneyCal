#ifndef MYCHART_H
#define MYCHART_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtCharts>

class mychart: public QMainWindow
{
    Q_OBJECT
public:
    mychart();
    void chartdisplay();
signals:
    void chartslot(QChart*);
};

#endif // MYCHART_H
