#pragma execution_character_set("utf-8")

#include "chart_view_preview.h"
#include "util.h"

#include <QMouseEvent>
#include <QWidget>

#include "Util.h"
#include "chart_view.h"

QMap<ChartView*, ChartViewPreview*> ChartViewPreview::s_view2preview;

ChartViewPreview::~ChartViewPreview()
{
	//����ȫ��Ԥ������
	s_view2preview.remove(m_view);
	//�ָ������״
	m_view->set_cursor_auto();
}

bool ChartViewPreview::is_previewing(ChartView* view)
{
	return s_view2preview.contains(view);
}

void ChartViewPreview::finish_all(ChartView* view)
{
	auto preview = s_view2preview.take(view);
	if (preview != nullptr)
	{
		preview->finish_preview();
		delete preview;
	}
}

void ChartViewPreview::begin_preview(ChartView* view)
{
	m_view = view;

	//һ����ͼ����ֻ����һ��Ԥ��
	finish_all(m_view);

	//��¼Ԥ��ͼԪ
	s_view2preview[m_view] = this;

	//��ʾcad���
	m_view->set_cursor_auto();

	set_step(BEGIN_PREVIEW);
}

void ChartViewPreview::finish_preview()
{
	set_step(BEGIN_PREVIEW);
	on_finish_preview();
}

void ChartViewPreview::advance_preview(const QPoint& point)
{
	QPointF pos = m_view->map_to_scene(point);
	on_advance_preview(pos);
}

void ChartViewPreview::on_mouse_move(ChartView* view, QMouseEvent* event)
{
	if (s_view2preview.contains(view))
	{
		s_view2preview[view]->on_mouse_move(event);
	}
}

void ChartViewPreview::on_mouse_move(QMouseEvent* event)
{
	QPointF pos = m_view->map_to_scene(event->pos());
	on_mouse_move(pos);
	m_view->redraw();
}

void ChartViewPreview::set_step(int step)
{
	m_step = step;
}

void ChartViewPreview::on_mouse_release(ChartView* view, QMouseEvent* event)
{
	if (!s_view2preview.contains(view)) return;

	auto preview = s_view2preview[view];

	if (event->button() == Qt::LeftButton)
	{
		preview->advance_preview(event->pos());
	}
	else if (event->button() == Qt::RightButton)
	{
		if (preview->step() == BEGIN_PREVIEW)
			delete preview;
		else preview->finish_preview();
	}
}
