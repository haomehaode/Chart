#ifndef CHART_VIEW_H
#define CHART_VIEW_H

#include "graph_global.h"
#include "graphics_item.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>


using namespace QtCharts;

class GRAPH_EXPORT ChartView : public  QGraphicsView
{
	Q_OBJECT

public:

	ChartView(QChart* chart, QWidget* parent = nullptr);

public:
	/** �ػ泡�� */
	void redraw();
	/** \brief ����ͼƬ*/
	bool save_picture(const QString& filename, const QSize& size = QSize(3050, 2050));
	/** ������ͼ��widget */
	QWidget* widget();
	/** ����������ͼ�Ĺ�� */
	void set_cursor_auto();
	/** ����ͼ����ת������������ */
	QPointF map_to_scene(const QPoint& pos);
	/** ����������ת������ͼ���� */
	QPoint map_from_scene(const QPointF& pos);
	/** ����ͼ����ת������Ļ���� */
	QPoint map_to_global(const QPoint& pos);
	/** ���ͼԪ */
	void add_item(GraphicsItem* item);
	/** ɾ��ͼԪ */
	void delete_item(GraphicsItem* item);
	/** ���ڻ�ͼ */
	bool is_previewing();

public slots:

	void slot_chart_config();

	void slot_series_config();

	void slot_axis_config();

protected:

	virtual void resizeEvent(QResizeEvent* event) override;

	virtual	void mousePressEvent(QMouseEvent* event) override;

	virtual void mouseMoveEvent(QMouseEvent* event) override;

	virtual void mouseReleaseEvent(QMouseEvent* event) override;

	virtual void keyPressEvent(QKeyEvent* event) override;

	virtual void wheelEvent(QWheelEvent* event) override;

	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
	/** ͼ�� */
	QChart* m_chart = nullptr;
	/** ��ѡ��ʼ�� */
	QPoint m_begin_point;
	/** ��ѡ������ */
	QPoint m_end_point;
	/** ��ק�� */
	QPoint m_old_point;
	/** �Ƿ���ק */
	bool m_isTranslate = false;
	/** ��ק��¼*/
	QPointF m_translate_pos;
};

#endif // CHART_VIEW_H