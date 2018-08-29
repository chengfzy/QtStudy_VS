#pragma once

#include <QFrame>
#include <QtWidgets>

class CropWidget : public QFrame
{
	Q_OBJECT

public:
	explicit CropWidget(QWidget *parent = nullptr);
	~CropWidget();

signals:
	void needMove(int width, int height);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	QRect getResizeGem(QRect oldGeo, QPoint mousePoint);

private:
	QPoint m_startPoint;
	QPoint m_oldPos;

	bool m_bMoving;
	bool m_bMouseDown;
	bool m_bLeft;
	bool m_bRight;
	bool m_bTop;
	bool m_bBottom;
	QLabel* m_pLabel;

};
