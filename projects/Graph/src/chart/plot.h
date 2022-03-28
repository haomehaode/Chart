#ifndef PLOT_H
#define PLOT_H

#include "graph_global.h"
#include <QtCharts/QChart>
#include <QtCharts/QPolarChart>
#include <QtCharts/QLegendMarker>
#include <QBoxLayout>
#include <QWidget>

using  namespace QtCharts;

class ChartView;
class ToolTip;

class GRAPH_EXPORT Plot : public QWidget
{
	Q_OBJECT

public:

	Plot(bool IsPolar=false, QWidget *parent = nullptr);

	~Plot();

public slots:
	/** �����ʾ */
	virtual void slot_tool_tip(QPointF point, bool state);
	/** ͼ����� */
	void slot_handle_marker_clicked();

public:
	/** ͼ����� */
	void add_title(const QString& name);
	/** ����ͼ�� */
	void connect_markers();
	/** ȡ��ͼ������ */
	void disconnect_markers();
	/** ��ʼ���� */
	void draw_line();
	/** ��ʼ����ͷ */
	void draw_arrows();

protected:
	/** ��ʼ��ͼ�� */
	virtual void init_chart() = 0;
	/** ��ʼ�������� */
	virtual void init_axis() = 0;
	/** ��ʼ��ϵ�� */
	virtual void init_series() = 0;

protected:
	virtual void resizeEvent(QResizeEvent* event) override;

protected:
	/** ͼ�� */
	QChart* m_chart = nullptr;
	/** ��ͼ */
	ChartView* m_chartview = nullptr;
	/** �����ʾ */
	ToolTip* m_tooltip = nullptr;
	/** X ��Сֵ */
	double m_min_x = DBL_MAX;
	/** X ���ֵ */
	double m_max_x = DBL_MIN;
	/** Y ��Сֵ */
	double m_min_y = DBL_MAX;
	/** Y ���ֵ */
	double m_max_y = DBL_MIN;
	/** Z ��Сֵ */
	double m_min_z = DBL_MAX;
	/** Z ���ֵ */
	double m_max_z = DBL_MIN;
};

#endif // PLOT_H