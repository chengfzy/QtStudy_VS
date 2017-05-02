#pragma once

#include <QtWidgets>

//CursorPosition
enum class CursorPosition
{
	Undefined,
	Middle,
	Top,
	Bottom,
	Left,
	Right,
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight
};

class PictureWidget : public QWidget
{
	Q_OBJECT
public:
	PictureWidget(QWidget *parent = nullptr);
	~PictureWidget();
	
public:
	void SetImage(const QPixmap& image);	//set image
	void SetLogo(const QPixmap& image);		//set logo

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	bool isPointNearSide(int sideCoord, int pointCoord);
	CursorPosition getCursorPosition(const QPointF& mousePosition);
	void updateCursor(const QPointF& mousePosition);		//update mouse cursor

	QRectF calculateImageGeometry(const QRectF& sourceGeometry, const QPointF& mouseDelta);

private:
	QPixmap m_logo;					//image
	CursorPosition m_cursorPosition;//cursor position
	bool m_bMousePressed;			//is mouse is pressed

	QSizeF m_logoRatio;

	QPointF m_startMousePos;
	QRectF m_lastLogoRect;
	QRectF m_logoRect;
	QColor m_borderColor;	
};