#ifndef PROBABILITY_PLOT_H
#define PROBABILITY_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include <QValueAxis>
#include <QCategoryAxis>
#include <QLineSeries>
#include <QScatterSeries>
#include "data.h"


class GRAPH_EXPORT ProbabilityPlot : public Plot
{
	Q_OBJECT

public:

	ProbabilityPlot(QWidget* parent = nullptr);

	~ProbabilityPlot();

public slots:

	 void slot_tool_tip(QPointF point, bool state) override;

public:

	void add_data(QList<double>& list, const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

protected:
	/** ���ݼ��� */
	void prepare_data(QList<double>& list);
	/** ����CDF */
	double calculate_cdf(int index, int n);

protected:
	/** ƽ��ֵ */
	double m_mean;
	/** ���� */
	double m_variance;
	/** ��׼�� */
	double m_sigma;
	/** ������ */
	int m_n;

protected:

	QLineSeries* m_line_center =nullptr ;

	QLineSeries* m_line_top = nullptr;

	QLineSeries* m_line_bottom = nullptr;
	
	QScatterSeries* m_scatter = nullptr;

	QValueAxis* m_axisX = nullptr;

	QCategoryAxis* m_axisY = nullptr;

	QList<Probability> m_probability_list;

	ScoreType m_score_type = Benard;

};

#endif // PROBABILITY_PLOT_H