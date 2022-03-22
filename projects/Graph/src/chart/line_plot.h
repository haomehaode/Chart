#ifndef LINE_PLOT_H
#define LINE_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include <QLineSeries>
#include <QValueAxis>
#include <QStack>

class GRAPH_EXPORT LinePlot : public Plot
{

public:

	LinePlot(QWidget *parent = Q_NULLPTR);

	~LinePlot();

public:

	void add_line(QList<QPointF>& poslist, const QString &name );

	void delete_line(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;


private:
	/** ���ݼ��� */
	void prepare_data(QList<QPointF>& poslist);

private:
	/** ���ƺ�ϵ��ӳ�� */
	QMap<QString, QLineSeries*> m_name2series;
	/** X �� */
	QValueAxis* m_axisX = nullptr;
	/** Y �� */
	QValueAxis* m_axisY = nullptr;
	/** ��¼�����᷶Χ */
	QStack<double> m_range[4];
};

#endif // LINE_PLOT_H