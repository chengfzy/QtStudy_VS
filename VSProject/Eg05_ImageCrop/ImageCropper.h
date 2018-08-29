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
	// �����ѧߧ�ӧڧ�� �ڧ٧�ҧ�ѧا֧ߧڧ� �էݧ� ��ҧ�֧٧ܧ�
	void setImage(const QPixmap& image);
	// �����ѧߧ�ӧڧ�� ��ӧ֧� ���ߧ� �ӧڧէا֧�� ��ҧ�֧٧ܧ�
	void setBackgroundColor(const QColor& backgroundColor);
	// �����ѧߧ�ӧڧ�� ��ӧ֧� ��ѧާܧ� ��ҧݧѧ��� ��ҧ�֧٧ܧ�
	void setCroppingRectBorderColor(const QColor& borderColor);
	// �����ѧߧ�ӧڧ�� ��������ڧ� ��ҧݧѧ��� �ӧ�է֧ݧ֧ߧڧ�
	void setProportion(const QSizeF& proportion);
	// ������ݧ�٧�ӧѧ�� ��ڧܧ�ڧ��ӧѧߧߧ�� ��������ڧ� ��ҧݧѧ��� �ӧڧէ֧ݧ֧ߧڧ�
	void setProportionFixed(const bool isFixed);

public:
	// ���ҧ�֧٧ѧ�� �ڧ٧�ҧ�ѧا֧ߧڧ�
	const QPixmap cropImage();

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);

private:
	// �����֧է֧ݧ֧ߧڧ� �ާ֧�����ݧ�ا֧ߧڧ� �ܧ������ �ߧѧ� �ӧڧէا֧���
	CursorPosition getcursorPosition(const QRectF& cropRect, const QPointF& mousePosition);
	// ���ҧߧ�ӧڧ�� �ڧܧ�ߧܧ� �ܧ������ �����ӧ֧���ӧ����� �ާ֧�����ݧ�ا֧ߧڧ� �ާ���
	void updateCursorIcon(const QPointF& mousePosition);

	// ����ݧ��ڧ�� ��ѧ٧ާ֧� �ӧڧէا֧�� ����ݧ� �֧ԧ� �ڧ٧ާ֧ߧ֧ߧڧ� �ާ����
	// --------
	// ����ߧ��ѧܧ��:
	// 1. ���֧��� �է�ݧا֧� �ӧ�٧�ӧѧ����, ���ݧ�ܧ� ���� �٧ѧاѧ��� �ܧߧ��ܧ� �ާ���
	//    (��.��. ���� ��֧�֧ާ֧�֧ߧڧ� �ڧݧ� �ڧ٧ާ֧ߧ֧ߧڧ� ��ѧ٧ާ֧�� �ӧڧէا֧��)
	// --------
	// �� ��ݧ��ѧ� �ߧ֧�էѧ�� �ӧ�٧ӧ�ѧ�ѧ֧� null-����ާ��ԧ�ݧ�ߧڧ�
	const QRectF calculateGeometry(const QRectF& sourceGeometry, const CursorPosition cursorPosition, const QPointF& mouseDelta);
	// ����ݧ��ڧ�� ��ѧ٧ާ֧� �ӧڧէا֧�� ����ݧ� �֧ԧ� �ڧ٧ާ֧ߧ֧ߧڧ� �ާ����
	// ���֧��� �ڧ٧ާ֧ߧ�֧� �ӧڧէا֧� �ߧ� �����ѧߧ�� �ߧѧ�ѧݧ�ߧ�� ��������ڧ� �������
	// ------
	// ����ߧ��ѧܧ��:
	// 1. ���֧��� �է�ݧا֧� �ӧ�٧�ӧѧ����, ���ݧ�ܧ� ���� �٧ѧاѧ��� �ܧߧ��ܧ� �ާ���
	//    (��.��. ���� ��֧�֧ާ֧�֧ߧڧ� �ڧݧ� �ڧ٧ާ֧ߧ֧ߧڧ� ��ѧ٧ާ֧�� �ӧڧէا֧��)
	const QRectF calculateGeometryWithCustomProportions(const QRectF& sourceGeometry, const CursorPosition cursorPosition,
		const QPointF& mouseDelta);
	// ����ݧ��ڧ�� ��ѧ٧ާ֧� �ӧڧէا֧�� ����ݧ� �֧ԧ� �ڧ٧ާ֧ߧ֧ߧڧ� �ާ����
	// ���֧��� �ڧ٧ާ֧ߧ�֧� �ӧڧէا֧� �����ѧߧ�� �ߧѧ�ѧݧ�ߧ�� ��������ڧ� �������
	// ------
	// ����ߧ��ѧܧ��:
	// 1. ���֧��� �է�ݧا֧� �ӧ�٧�ӧѧ����, ���ݧ�ܧ� ���� �٧ѧاѧ��� �ܧߧ��ܧ� �ާ���
	//    (��.��. ���� ��֧�֧ާ֧�֧ߧڧ� �ڧݧ� �ڧ٧ާ֧ߧ֧ߧڧ� ��ѧ٧ާ֧�� �ӧڧէا֧��)
	const QRectF calculateGeometryWithFixedProportions(const QRectF &_sourceGeometry, const CursorPosition cursorPosition,
		const QPointF &_mouseDelta, const QSizeF &_deltas);

	//is the point next to the coordinate of the side
	bool isPointNearSide(const int sideCoordinate, const int pointCoordinate);

private:
	// ���٧�ҧ�ѧا֧ߧڧ� �էݧ� ��ҧ�֧٧ܧ�
	QPixmap m_image;
	// ���ҧݧѧ��� ��ҧ�֧٧ܧ�
	QRectF m_croppingRect;
	// �����ݧ֧էߧ�� ��ڧܧ�ڧ��ӧѧߧߧѧ� ��ҧݧѧ��� ��ҧ�֧٧ܧ�
	QRectF m_lastStaticCroppingRect;
	// ����٧ڧ�ڧ� �ܧ������ ���ߧ��ڧ�֧ݧ�ߧ� ��ҧݧѧ��� ��ҧ�֧٧ܧ�
	CursorPosition m_cursorPosition;
	// ���ѧاѧ�� �ݧ� �ݧ֧ӧѧ� �ܧߧ��ܧ� �ާ���
	bool m_bMousePressed;
	// ���ڧܧ�ڧ��ӧѧ�� ��������ڧ� ��ҧݧѧ��� ��ҧ�֧٧ܧ�
	bool m_bProportionFixed;
	// ���ѧ�ѧݧ�ߧѧ� ���٧ڧ�ڧ� �ܧ������ ���� �ڧ٧ާ֧ߧ֧ߧڧ� ��ѧ٧ާ֧�� ��ҧݧѧ��� ��ҧ�֧٧ܧ�
	QPointF m_startMousePos;
	// ���������ڧ�
	QSizeF m_proportion;
	// ����ڧ�ѧ�֧ߧڧ�
	// width  - ���ڧ�ѧ�֧ߧڧ� ��� x
	// height - ���ڧ�ѧ�֧ߧڧ� ��� y
	QSizeF m_deltas;
	// ���ӧ֧� �٧ѧݧڧӧܧ� ���ߧ� ���� �ڧ٧�ҧ�ѧا֧ߧڧ֧�
	QColor m_backgroundColor;
	// ���ӧ֧� ��ѧާܧ� ��ҧݧѧ��� ��ҧ�֧٧ܧ�
	QColor m_croppingRectBorderColor;
};
