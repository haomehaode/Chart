#ifndef SCATTER_PLOT_H 
#define SCATTER_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include <QScatterSeries>
#include <QValueAxis>
#include <QStack>

class GRAPH_EXPORT ScatterPlot: public Plot
{

public:

	ScatterPlot(QWidget* parent = Q_NULLPTR);

	~ScatterPlot();

public:

	void add_scatter(QList<QPointF>& poslist, const QString& name);

	void delete_scatter(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** ���ݼ��� */
	void prepare_data(QList<QPointF>& poslist);

private:
	/** ���ƺ�ϵ��ӳ�� */
	QMap<QString, QScatterSeries*> m_name2series;
	/** X �� */
	QValueAxis* m_axisX = nullptr;
	/** Y �� */
	QValueAxis* m_axisY = nullptr;
	/** ��¼�����᷶Χ */
	QStack<double> m_range[4];
};

#endif // SCATTER_PLOT_H