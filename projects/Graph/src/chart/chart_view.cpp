#pragma execution_character_set("utf-8")

#include "chart_view.h"
#include "QGraphicsView"
#include "QAbstractScrollArea"
#include "qmath.h"
#include "QMenu"
#include "axis_config.h"
#include "series_config.h"
#include "chart_config.h"
#include <SizeGripItem.h>
#include "chart_view_preview.h"


namespace
{
	class RectResizer : public SizeGripItem::Resizer
	{
	public:
		virtual void operator()(QGraphicsItem* item, const QRectF& rect)
		{
			QGraphicsRectItem* rectItem =dynamic_cast<QGraphicsRectItem*>(item);
			if (rectItem)
				rectItem->setRect(rect);
		}
	};

	class EllipseResizer : public SizeGripItem::Resizer
	{
	public:
		virtual void operator()(QGraphicsItem* item, const QRectF& rect)
		{
			QGraphicsEllipseItem* ellipseItem = dynamic_cast<QGraphicsEllipseItem*>(item);
			if (ellipseItem)
				ellipseItem->setRect(rect);
		}
	};
}


ChartView::ChartView(QChart* chart, QWidget* parent)
	: QGraphicsView(new QGraphicsScene, parent), m_chart(chart), m_old_point(0, 0), m_translate_pos(0, 0)
{
	setRenderHint(QPainter::Antialiasing);

	//ʹ�ܽ��յ��������ͼ�����ƶ����¼�
	setMouseTracking(true);

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setViewportUpdateMode(FullViewportUpdate);

	m_chart->setZValue(0);
	m_chart->setSelected(true);
	scene()->addItem(m_chart);

	//QGraphicsEllipseItem* item = new QGraphicsEllipseItem(0, 0, 100, 100);//x,y Ϊ���Ͻǵ�ͼԪ�ֲ����꣬ͼԪ���ĵ�Ϊ0,0
	//item->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
	//item->setZValue(1);
	//item->setPos(10, 10);
	//item->setSelected(true);
	//scene()->addItem(item);

	//QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(0, 0, 320, 240));
	//rectItem->setBrush(Qt::red);
	//rectItem->setPen(Qt::NoPen);
	//rectItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
	//scene()->addItem(rectItem);

	//QGraphicsEllipseItem* ellipseItem =
	//	new QGraphicsEllipseItem(QRectF(0, 0, 200, 200));
	//ellipseItem->setBrush(Qt::blue);
	//ellipseItem->setPen(Qt::NoPen);
	//ellipseItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
	//scene()->addItem(ellipseItem);

	//SizeGripItem* rectSizeGripItem =new SizeGripItem(new RectResizer, rectItem);
	//SizeGripItem* ellipseSizeGripItem =new SizeGripItem(new EllipseResizer, ellipseItem);

}


void ChartView::redraw()
{
	viewport()->update();
}

bool ChartView::save_picture(const QString& filename, const QSize& size )
{
	return true;
}

QWidget* ChartView::widget()
{
	return this;
}

void ChartView::slot_chart_config()
{
	ChartConfig dlg;
	dlg.setModal(false);
	dlg.exec();
}

void ChartView::slot_series_config()
{
	SeriesConfig dlg;
	dlg.setModal(false);
	dlg.exec();
}

void ChartView::slot_axis_config()
{
	AxisConfig dlg;
	dlg.setModal(false);
	dlg.exec();
}

void ChartView::resizeEvent(QResizeEvent* event)
{
	if (scene()) {
		scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
		m_chart->resize(event->size());
	}
	QGraphicsView::resizeEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent* event)
{
	//���������£���¼beginPoint
	if (event->button() == Qt::LeftButton)
		m_begin_point = event->pos();
	else if (event->button() == Qt::MiddleButton)
	{
		m_isTranslate = true;
		m_old_point = event->pos();
		set_cursor_auto();
	}
	//else if (event->button() == Qt::RightButton)
	//{
	//	QPointF pointScene = mapToScene(event->pos()); //ת����Scene����
	//	QGraphicsItem* item = NULL;
	//	item = scene()->itemAt(pointScene, transform()); //��ȡ����µĻ�ͼ��
	//	auto lost= scene()->items(pointScene);

	//	QMenu menu(this);
	//	menu.addAction(tr("ͼ������"), this, SLOT(slot_chart_config()));
	//	menu.addAction(tr("��������"), this, SLOT(slot_series_config()));
	//	menu.addAction(tr("����������"), this, SLOT(slot_axis_config()));
	//	menu.addSeparator();
	//	menu.addAction(tr("����ͼƬ"));
	//	menu.addAction(tr("��ӡ"));
	//	menu.exec(QCursor::pos());
	//}
	QGraphicsView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent* event)
{
	if (is_previewing())
		ChartViewPreview::on_mouse_move(this, event);
	else if (m_isTranslate)
	{
		QPointF delta = event->pos() - m_old_point;
		m_translate_pos += QPointF(-delta.x(), delta.y());
		m_chart->scroll(-delta.x(), delta.y());
		m_old_point = event->pos();
	}
	QGraphicsView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{ 
		//�������ͷţ���ȡ���ο��endPoint,��������
		m_end_point = event->pos();
		//QRectF  rectF;
		//rectF.setTopLeft(this->m_begin_point);
		//rectF.setBottomRight(this->m_end_point);
		//m_chart->zoomIn(rectF);
	}
	else if (event->button() == Qt::RightButton)
	{
		m_chart->zoomReset(); //����Ҽ��ͷţ�resetZoom
		m_chart->scroll(-m_translate_pos.x(), -m_translate_pos.y());
		m_translate_pos.setX(0);
		m_translate_pos.setY(0);
	}
	else if (event->button() == Qt::MiddleButton)
	{
		m_isTranslate = false;
		set_cursor_auto();
	}
	if (is_previewing())
		ChartViewPreview::on_mouse_release(this, event);
	QGraphicsView::mouseReleaseEvent(event);
}

void ChartView::keyPressEvent(QKeyEvent* event)
{
	switch (event->key()) {
	case Qt::Key_Plus:
		m_chart->zoomIn();
		break;
	case Qt::Key_Minus:
		m_chart->zoomOut();
		break;
	case Qt::Key_Left:
		m_chart->scroll(-10, 0);
		break;
	case Qt::Key_Right:
		m_chart->scroll(10, 0);
		break;
	case Qt::Key_Up:
		m_chart->scroll(0, 10);
		break;
	case Qt::Key_Down:
		m_chart->scroll(0, -10);
		break;
	default:
		QGraphicsView::keyPressEvent(event);
		break;
	}
}

void ChartView::wheelEvent(QWheelEvent* event)
{
	// ���ñ���
	qreal ratio = std::pow(0.999, event->delta());
	// 1. ��ȡ��ͼ������Ϣ
	QRectF rect = m_chart->plotArea();
	QPointF pos = rect.center();
	// 2. ˮƽ����
	rect.setWidth(rect.width() * ratio);
	// 3. ��ֱ����
	rect.setHeight(rect.height() * ratio);
	// 4. �����ӵ㣬���������λ�þ������ֲ���(�ȱȻ��㣬����һ�����)
	QPointF center(2 * pos - event->pos() - (pos - event->pos()) / ratio);
	// 5. �����ӵ�
	rect.moveCenter(center);
	// 6. �ύ���ŵ���
	m_chart->zoomIn(rect);

	QGraphicsView::wheelEvent(event);

}

void ChartView::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		//QPointF pointScene = mapToScene(event->pos()); //ת����Scene����
		//QGraphicsItem* item = NULL;
		//item = scene()->itemAt(pointScene, transform()); //��ȡ����µĻ�ͼ��
		//auto lost = scene()->items(pointScene);

		//QMenu menu(this);
		//menu.addAction(tr("ͼ������"));
		//menu.addAction(tr("��������"));
		//menu.addAction(tr("����������"));
		//menu.addSeparator();
		//menu.addAction(tr("����ͼƬ"));
		//menu.addAction(tr("��ӡ"));
		//menu.exec(QCursor::pos());
		//scene()->clearSelection();
	}
	QGraphicsView::mouseDoubleClickEvent(event);
}

void ChartView::set_cursor_auto()
{
	if (m_isTranslate) 
		setCursor(Qt::ClosedHandCursor);
	else if (ChartViewPreview::is_previewing(this))
		setCursor(Qt::CrossCursor);
	else 
		setCursor(Qt::ArrowCursor);
}

QPointF ChartView::map_to_scene(const QPoint& pos)
{
	QPointF pt = mapToScene(pos);
	pt.setY(-pt.y());
	return pt;
}

QPoint ChartView::map_from_scene(const QPointF& pos)
{
	QPointF p(pos.x(), -pos.y());
	return mapFromScene(p);
}

QPoint ChartView::map_to_global(const QPoint& pos)
{
	return mapToGlobal(pos);
}

void ChartView::add_item(GraphicsItem* item)
{
	item->apply();
	item->set_view(this);
	scene()->addItem(dynamic_cast<QGraphicsItem*>(item));
}

void ChartView::delete_item(GraphicsItem* item)
{
	scene()->removeItem(dynamic_cast<QGraphicsItem*> (item));
}

bool ChartView::is_previewing()
{
	return ChartViewPreview::is_previewing(this);
}
