#pragma once

#include <QtWidgets>

//CursorPosition
enum CursorPosition
{
	CursorPositionUndefined,
	CursorPositionMiddle,
	CursorPositionTop,
	CursorPositionBottom,
	CursorPositionLeft,
	CursorPositionRight,
	CursorPositionTopLeft,
	CursorPositionTopRight,
	CursorPositionBottomLeft,
	CursorPositionBottomRight
};

class ImageCropper : public QWidget
{
	Q_OBJECT

public:
	ImageCropper(QWidget *parent = nullptr);
	~ImageCropper();

public slots:
	// §µ§ã§ä§Ñ§ß§à§Ó§Ú§ä§î §Ú§Ù§à§Ò§â§Ñ§Ø§Ö§ß§Ú§Ö §Õ§Ý§ñ §à§Ò§â§Ö§Ù§Ü§Ú
	void setImage(const QPixmap& image);
	// §µ§ã§ä§Ñ§ß§à§Ó§Ú§ä§î §è§Ó§Ö§ä §æ§à§ß§Ñ §Ó§Ú§Õ§Ø§Ö§ä§Ñ §à§Ò§â§Ö§Ù§Ü§Ú
	void setBackgroundColor(const QColor& backgroundColor);
	// §µ§ã§ä§Ñ§ß§à§Ó§Ú§ä§î §è§Ó§Ö§ä §â§Ñ§Þ§Ü§Ú §à§Ò§Ý§Ñ§ã§ä§Ú §à§Ò§â§Ö§Ù§Ü§Ú
	void setCroppingRectBorderColor(const QColor& borderColor);
	// §µ§ã§ä§Ñ§ß§à§Ó§Ú§ä§î §á§â§à§á§à§â§è§Ú§Ú §à§Ò§Ý§Ñ§ã§ä§Ú §Ó§í§Õ§Ö§Ý§Ö§ß§Ú§ñ
	void setProportion(const QSizeF& proportion);
	// §ª§ã§á§à§Ý§î§Ù§à§Ó§Ñ§ä§î §æ§Ú§Ü§ã§Ú§â§à§Ó§Ñ§ß§ß§í§Ö §á§â§à§á§à§â§è§Ú§Ú §à§Ò§Ý§Ñ§ã§ä§Ú §Ó§Ú§Õ§Ö§Ý§Ö§ß§Ú§ñ
	void setProportionFixed(const bool isFixed);

public:
	// §°§Ò§â§Ö§Ù§Ñ§ä§î §Ú§Ù§à§Ò§â§Ñ§Ø§Ö§ß§Ú§Ö
	const QPixmap cropImage();

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);

private:
	// §°§á§â§Ö§Õ§Ö§Ý§Ö§ß§Ú§Ö §Þ§Ö§ã§ä§à§á§à§Ý§à§Ø§Ö§ß§Ú§ñ §Ü§å§â§ã§à§â§Ñ §ß§Ñ§Õ §Ó§Ú§Õ§Ø§Ö§ä§à§Þ
	CursorPosition getcursorPosition(const QRectF& cropRect, const QPointF& mousePosition);
	// §°§Ò§ß§à§Ó§Ú§ä§î §Ú§Ü§à§ß§Ü§å §Ü§å§â§ã§à§â§Ñ §ã§à§à§ä§Ó§Ö§ä§ã§ä§Ó§å§ð§ë§å§ð §Þ§Ö§ã§ä§à§á§à§Ý§à§Ø§Ö§ß§Ú§ð §Þ§í§ê§Ú
	void updateCursorIcon(const QPointF& mousePosition);

	// §±§à§Ý§å§é§Ú§ä§î §â§Ñ§Ù§Þ§Ö§â §Ó§Ú§Õ§Ø§Ö§ä§Ñ §á§à§ã§Ý§Ö §Ö§Ô§à §Ú§Ù§Þ§Ö§ß§Ö§ß§Ú§ñ §Þ§í§ê§î§ð
	// --------
	// §¬§à§ß§ä§â§Ñ§Ü§ä§í:
	// 1. §®§Ö§ä§à§Õ §Õ§à§Ý§Ø§Ö§ß §Ó§í§Ù§í§Ó§Ñ§ä§î§ã§ñ, §ä§à§Ý§î§Ü§à §á§â§Ú §Ù§Ñ§Ø§Ñ§ä§à§Û §Ü§ß§à§á§Ü§Ö §Þ§í§ê§Ú
	//    (§ä.§Ö. §á§â§Ú §á§Ö§â§Ö§Þ§Ö§ë§Ö§ß§Ú§Ú §Ú§Ý§Ú §Ú§Ù§Þ§Ö§ß§Ö§ß§Ú§Ú §â§Ñ§Ù§Þ§Ö§â§Ñ §Ó§Ú§Õ§Ø§Ö§ä§Ñ)
	// --------
	// §£ §ã§Ý§å§é§Ñ§Ö §ß§Ö§å§Õ§Ñ§é§Ú §Ó§à§Ù§Ó§â§Ñ§ë§Ñ§Ö§ä null-§á§â§ñ§Þ§à§å§Ô§à§Ý§î§ß§Ú§Ü
	const QRectF calculateGeometry(const QRectF& sourceGeometry, const CursorPosition cursorPosition, const QPointF& mouseDelta);
	// §±§à§Ý§å§é§Ú§ä§î §â§Ñ§Ù§Þ§Ö§â §Ó§Ú§Õ§Ø§Ö§ä§Ñ §á§à§ã§Ý§Ö §Ö§Ô§à §Ú§Ù§Þ§Ö§ß§Ö§ß§Ú§ñ §Þ§í§ê§î§ð
	// §®§Ö§ä§à§Õ §Ú§Ù§Þ§Ö§ß§ñ§Ö§ä §Ó§Ú§Õ§Ø§Ö§ä §ß§Ö §ã§à§ç§â§Ñ§ß§ñ§ñ §ß§Ñ§é§Ñ§Ý§î§ß§í§ç §á§â§à§á§à§â§è§Ú§Û §ã§ä§à§â§à§ß
	// ------
	// §¬§à§ß§ä§â§Ñ§Ü§ä§í:
	// 1. §®§Ö§ä§à§Õ §Õ§à§Ý§Ø§Ö§ß §Ó§í§Ù§í§Ó§Ñ§ä§î§ã§ñ, §ä§à§Ý§î§Ü§à §á§â§Ú §Ù§Ñ§Ø§Ñ§ä§à§Û §Ü§ß§à§á§Ü§Ö §Þ§í§ê§Ú
	//    (§ä.§Ö. §á§â§Ú §á§Ö§â§Ö§Þ§Ö§ë§Ö§ß§Ú§Ú §Ú§Ý§Ú §Ú§Ù§Þ§Ö§ß§Ö§ß§Ú§Ú §â§Ñ§Ù§Þ§Ö§â§Ñ §Ó§Ú§Õ§Ø§Ö§ä§Ñ)
	const QRectF calculateGeometryWithCustomProportions(const QRectF& sourceGeometry, const CursorPosition cursorPosition,
		const QPointF& mouseDelta);
	// §±§à§Ý§å§é§Ú§ä§î §â§Ñ§Ù§Þ§Ö§â §Ó§Ú§Õ§Ø§Ö§ä§Ñ §á§à§ã§Ý§Ö §Ö§Ô§à §Ú§Ù§Þ§Ö§ß§Ö§ß§Ú§ñ §Þ§í§ê§î§ð
	// §®§Ö§ä§à§Õ §Ú§Ù§Þ§Ö§ß§ñ§Ö§ä §Ó§Ú§Õ§Ø§Ö§ä §ã§à§ç§â§Ñ§ß§ñ§ñ §ß§Ñ§é§Ñ§Ý§î§ß§í§Ö §á§â§à§á§à§â§è§Ú§Ú §ã§ä§à§â§à§ß
	// ------
	// §¬§à§ß§ä§â§Ñ§Ü§ä§í:
	// 1. §®§Ö§ä§à§Õ §Õ§à§Ý§Ø§Ö§ß §Ó§í§Ù§í§Ó§Ñ§ä§î§ã§ñ, §ä§à§Ý§î§Ü§à §á§â§Ú §Ù§Ñ§Ø§Ñ§ä§à§Û §Ü§ß§à§á§Ü§Ö §Þ§í§ê§Ú
	//    (§ä.§Ö. §á§â§Ú §á§Ö§â§Ö§Þ§Ö§ë§Ö§ß§Ú§Ú §Ú§Ý§Ú §Ú§Ù§Þ§Ö§ß§Ö§ß§Ú§Ú §â§Ñ§Ù§Þ§Ö§â§Ñ §Ó§Ú§Õ§Ø§Ö§ä§Ñ)
	const QRectF calculateGeometryWithFixedProportions(const QRectF &_sourceGeometry, const CursorPosition cursorPosition,
		const QPointF &_mouseDelta, const QSizeF &_deltas);

	//is the point next to the coordinate of the side
	bool isPointNearSide(const int sideCoordinate, const int pointCoordinate);

private:
	// §ª§Ù§à§Ò§â§Ñ§Ø§Ö§ß§Ú§Ö §Õ§Ý§ñ §à§Ò§â§Ö§Ù§Ü§Ú
	QPixmap m_image;
	// §°§Ò§Ý§Ñ§ã§ä§î §à§Ò§â§Ö§Ù§Ü§Ú
	QRectF m_croppingRect;
	// §±§à§ã§Ý§Ö§Õ§ß§ñ§ñ §æ§Ú§Ü§ã§Ú§â§à§Ó§Ñ§ß§ß§Ñ§ñ §à§Ò§Ý§Ñ§ã§ä§î §à§Ò§â§Ö§Ù§Ü§Ú
	QRectF m_lastStaticCroppingRect;
	// §±§à§Ù§Ú§è§Ú§ñ §Ü§å§â§ã§à§â§Ñ §à§ä§ß§à§ã§Ú§ä§Ö§Ý§î§ß§à §à§Ò§Ý§Ñ§ã§ä§Ú §à§Ò§â§Ö§Ù§Ü§Ú
	CursorPosition m_cursorPosition;
	// §©§Ñ§Ø§Ñ§ä§Ñ §Ý§Ú §Ý§Ö§Ó§Ñ§ñ §Ü§ß§à§á§Ü§Ñ §Þ§í§ê§Ú
	bool m_bMousePressed;
	// §¶§Ú§Ü§ã§Ú§â§à§Ó§Ñ§ä§î §á§â§à§á§à§â§è§Ú§Ú §à§Ò§Ý§Ñ§ã§ä§Ú §à§Ò§â§Ö§Ù§Ü§Ú
	bool m_bProportionFixed;
	// §¯§Ñ§é§Ñ§Ý§î§ß§Ñ§ñ §á§à§Ù§Ú§è§Ú§ñ §Ü§å§â§ã§à§â§Ñ §á§â§Ú §Ú§Ù§Þ§Ö§ß§Ö§ß§Ú§Ú §â§Ñ§Ù§Þ§Ö§â§Ñ §à§Ò§Ý§Ñ§ã§ä§Ú §à§Ò§â§Ö§Ù§Ü§Ú
	QPointF m_startMousePos;
	// §±§â§à§á§à§â§è§Ú§Ú
	QSizeF m_proportion;
	// §±§â§Ú§â§Ñ§ë§Ö§ß§Ú§ñ
	// width  - §á§â§Ú§â§Ñ§ë§Ö§ß§Ú§Ö §á§à x
	// height - §á§â§Ú§â§Ñ§ë§Ö§ß§Ú§Ö §á§à y
	QSizeF m_deltas;
	// §¸§Ó§Ö§ä §Ù§Ñ§Ý§Ú§Ó§Ü§Ú §æ§à§ß§Ñ §á§à§Õ §Ú§Ù§à§Ò§â§Ñ§Ø§Ö§ß§Ú§Ö§Þ
	QColor m_backgroundColor;
	// §¸§Ó§Ö§ä §â§Ñ§Þ§Ü§Ú §à§Ò§Ý§Ñ§ã§ä§Ú §à§Ò§â§Ö§Ù§Ü§Ú
	QColor m_croppingRectBorderColor;
};
