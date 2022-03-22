#ifndef GRAPHICS_ITEM_H
#define GRAPHICS_ITEM_H

#include "QGraphicsItem"

class ChartView;

class GraphicsItem : public QGraphicsObject
{
public:
	/** ���캯�� */
	GraphicsItem();
	/** ����������ͼ */
	void set_view(ChartView* view);
	/** ��ȡ������ͼ */
	ChartView* view();
	/**
	* ͼԪ���ݱ��ʱ���ֶ����øýӿ���Ӧ���µ����ݣ�
	* ͼԪ����ǰ���Զ����øýӿ��Ա���ʾ��ȷ����״��
	*/
	void apply();

protected:
	/** ��ͼ���� */
	virtual QRectF boundingRect() const override;
	/** ��ͼ���� */
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	/** ��¡��������ʵ�� */
	virtual GraphicsItem* clone() { return nullptr; }
	/** ���ݸ��¼����Χ�У�������ʵ�� */
	virtual void on_apply() {}
	/** ����ͼ��������ʵ�� */
	virtual void on_paint(QPainter* painter) {}

private:
	/** ������ͼ */
	ChartView* m_view = nullptr;
};

#endif // GRAPHICS_ITEM_H