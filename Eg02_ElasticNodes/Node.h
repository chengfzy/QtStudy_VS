#pragma once

#include <QGraphicsItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>

class Edge;
class GraphWidget;

class Node : public QGraphicsItem
{
public:
	Node(GraphWidget *graphWidget);

	void addEdge(Edge* edge);
	QList<Edge*> edges() const;

	enum { Type = UserType + 1 };
	int type() const override;

	void calculateForces();
	bool advance();

	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
	QList<Edge*> edgeList;
	QPointF newPos;
	GraphWidget *graph;
};
