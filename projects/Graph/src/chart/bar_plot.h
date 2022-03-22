#ifndef BAR_PLOT_H
#define BAR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QLineSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QStack>
#include <QtCharts/QBarSet>
#include <QBarSeries>

class GRAPH_EXPORT BarPlot : public Plot
{
	Q_OBJECT

public:

	BarPlot(QWidget* parent = nullptr);

	~BarPlot();

public:

	void set_axis(QList<QString> list);

	void add_bar(QList<double>& value_list, const QString& name);

	void delete_bar(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;


private:
	/** ���ݼ��� */
	void prepare_data(QList<double>& value_list);

private:
	/** ���ƺ�ϵ��ӳ�� */
	QMap<QString, QBarSet*> m_name2series;

	QBarSeries* m_series = nullptr;
	/** X ��̶ȼ��� */
	QStringList m_axisx_list;
	/** X �� */
	QBarCategoryAxis* m_axisX =nullptr;
	/** Y �� */
	QValueAxis* m_axisY = nullptr;
	/** ��¼�����᷶Χ */
	QStack<double> m_range[2];

};

#endif // BAR_PLOT_H