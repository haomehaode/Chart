#ifndef BOXBAR_PLOT_H
#define BOXBAR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QBoxPlotSeries>
#include <QBoxSet>

class GRAPH_EXPORT BoxBarPlot : public Plot
{
	Q_OBJECT

public:

	BoxBarPlot(QWidget* parent = nullptr);

	~BoxBarPlot();

	void set_type(BoxBarType type);

public:

	void set_data(QList<BoxData> &list);

	void add_boxbar(BoxData& data);

	void delete_boxbar(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** ���ƺ�ϵ��ӳ�� */
	QMap<QString, QBoxSet*> m_name2series;
	/** X �� */
	QBarCategoryAxis* m_axisX = nullptr;
	/** Y �� */
	QValueAxis* m_axisY = nullptr;
	/** X �� */
	QStringList m_axisx_list;
	/** ����ͼ */
	QBoxPlotSeries* m_series = nullptr;
	/** �滭ģʽ */
	BoxBarType m_boxbartype = MEAN;

};

#endif // BOX_BAR_PLOT_H