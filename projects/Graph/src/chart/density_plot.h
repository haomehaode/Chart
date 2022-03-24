#ifndef DENSITY_PLOT_H
#define DENSITY_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QScatterSeries>
#include <QValueAxis>

class ColorBar;

class GRAPH_EXPORT DensityPlot : public Plot
{
	Q_OBJECT

public:

	DensityPlot(QWidget* parent = nullptr);

	~DensityPlot();

public:

	void set_data(QList<QPointF>& pos_list);

	void clear_data();

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:

	double squareDistance(DensityPoint a, DensityPoint b);

	void calculateDensity(QVector<DensityPoint>& dataset, float Eps);


private:
	/** ��ɫ�� */
	ColorBar* m_color_item = nullptr;
	/** X �� */
	QValueAxis* m_axisX = nullptr;
	/** Y �� */
	QValueAxis* m_axisY = nullptr;
	/** �ܶ�ֵ��ɢ�� */
	QMap<int, QScatterSeries*> value2series;
	/** �ܶȰ뾶 */
	double radius = 1;
};

#endif // DENSITY_PLOT_H