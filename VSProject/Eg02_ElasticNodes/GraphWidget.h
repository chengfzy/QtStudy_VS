#pragma once

#include <QGraphicsView>

class Node;

class GraphWidget : public QGraphicsView
{

public:
	GraphWidget(QWidget *parent = nullptr);

	void itemMoved();

public:
	void shuffle();
	void zoomIn();
	void zoomOut();

protected:
	void keyPressEvent(QKeyEvent* event) override;
	void timerEvent(QTimerEvent* event)	override;
	void wheelEvent(QWheelEvent* event) override;

	void drawBackground(QPainter* painter, const QRectF& rect) override;
	void scaleView(qreal scaleFactor);

private:
	int timerId;
	Node* centerNode;
};
