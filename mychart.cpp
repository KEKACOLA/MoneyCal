#include "mychart.h"
#include <QtCharts/QChartView>//显示图表
#include <QtCharts/QLineSeries>//线系列
QT_CHARTS_USE_NAMESPACE

mychart::mychart()
{

}

void mychart::chartdisplay()
{
    QList<QLineSeries*> m_series;
    QLineSeries *series = new QLineSeries();
    m_series.append(series);
    series->setName(QString("存款"));
    series->setColor(QColor(255,0,255));
    series->setVisible(true);
    series->setPointLabelsVisible(true);
    series->setPointLabelsColor(QColor(255,255,255));
    series->setPointLabelsFont(QFont("微软雅黑"));
    series->setPointLabelsFormat("@yPoint");
    series->setPointsVisible(true);
    for(int month=0;month<12;month++)
    {
        series->append(month,month*10);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("存款曲线");
    chart->setTitleBrush(QBrush(QColor(255,170,255)));
    chart->setTitleFont(QFont("微软雅黑"));
    chart->legend()->setVisible(true);
    emit chartslot(chart);
}
