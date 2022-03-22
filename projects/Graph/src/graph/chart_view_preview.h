#ifndef CHART_VIEW_PREVIEW_H
#define CHART_VIEW_PREVIEW_H

#include <QHash>
#include <QPointF>
#include <QLabel>

class ChartView;
class QMouseEvent;

/** ��ʼԤ�� */
#define BEGIN_PREVIEW -1

class ChartViewPreview 
{

public:

	virtual ~ChartViewPreview();
	/** �Ƿ�����Ԥ�� */
	static bool is_previewing(ChartView* view);
	/** ��ɲ��˳����еĻ��� */
	static void finish_all(ChartView* view);

	static void on_mouse_move(ChartView* view, QMouseEvent* event);

	static void on_mouse_release(ChartView* view, QMouseEvent* event);

public:
	/**
	* \brief ����ʵ�֣����ƽ����ƽ�
	* @param point ����ڳ���������
	*/
	virtual void on_advance_preview(QPointF& point) {}
	/** ����ʵ�֣����ͼԪ���� */
	virtual void on_finish_preview() {}

protected:
	/** ��������,��ʼԤ�� */
	void begin_preview(ChartView* view);
	/**
	* \brief ����ʵ�֣������������ͼ����ͼ�����ƶ�
	* @param point ����ڳ���������
	*/
	virtual void on_mouse_move(QPointF& point) {}
	/** ��ȡԤ������ */
	int step() const { return m_step; }
	/** ����Ԥ������ */
	void set_step(int step);

private:
	/** ��ɻ��Ʋ��� */
	void finish_preview();
	/** �ƽ����ƽ��� */
	void advance_preview(const QPoint& point);
	/** �������ͼ���ƶ� */
	void on_mouse_move(QMouseEvent* event);

protected:

	ChartView* m_view = nullptr;

private:
	//���ڻ��Ƶ�ͼԪ��key ��ͼ�� value Ԥ��ͼԪ
	static QMap<ChartView*, ChartViewPreview*> s_view2preview;
	//����ɵĲ���
	int m_step;
};

#endif // CHART_VIEW_PREVIEW_H