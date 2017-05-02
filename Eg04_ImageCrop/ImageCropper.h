#pragma once

#include <QWidget>


namespace
{
	const QRect INIT_CROPPING_RECT = QRect();
	const QSizeF INIT_PROPORTION = QSizeF(1.0, 1.0);
}

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


class ImageCropperPrivate
{
public:
	ImageCropperPrivate() :
		imageForCropping(QPixmap()),
		croppingRect(INIT_CROPPING_RECT),
		lastStaticCroppingRect(QRect()),
		cursorPosition(CursorPositionUndefined),
		isMousePressed(false),
		isProportionFixed(false),
		startMousePos(QPoint()),
		proportion(INIT_PROPORTION),
		deltas(INIT_PROPORTION),
		backgroundColor(Qt::black),
		croppingRectBorderColor(Qt::white)
	{}

public:
	// Изображение для обрезки
	QPixmap imageForCropping;
	// Область обрезки
	QRectF croppingRect;
	// Последняя фиксированная область обрезки
	QRectF lastStaticCroppingRect;
	// Позиция курсора относительно области обрезки
	CursorPosition cursorPosition;
	// Зажата ли левая кнопка мыши
	bool isMousePressed;
	// Фиксировать пропорции области обрезки
	bool isProportionFixed;
	// Начальная позиция курсора при изменении размера области обрезки
	QPointF startMousePos;
	// Пропорции
	QSizeF proportion;
	// Приращения
	// width  - приращение по x
	// height - приращение по y
	QSizeF deltas;
	// Цвет заливки фона под изображением
	QColor backgroundColor;
	// Цвет рамки области обрезки
	QColor croppingRectBorderColor;
};


class ImageCropper : public QWidget
{
	Q_OBJECT

public:
	ImageCropper(QWidget *parent = 0);
	~ImageCropper();

	public slots:
	// Установить изображение для обрезки
	void setImage(const QPixmap& _image);
	// Установить цвет фона виджета обрезки
	void setBackgroundColor(const QColor& _backgroundColor);
	// Установить цвет рамки области обрезки
	void setCroppingRectBorderColor(const QColor& _borderColor);
	// Установить пропорции области выделения
	void setProportion(const QSizeF& _proportion);
	// Использовать фиксированные пропорции области виделения
	void setProportionFixed(const bool _isFixed);

public:
	// Обрезать изображение
	const QPixmap cropImage();

protected:
	virtual void paintEvent(QPaintEvent* _event);
	virtual void mousePressEvent(QMouseEvent* _event);
	virtual void mouseMoveEvent(QMouseEvent* _event);
	virtual void mouseReleaseEvent(QMouseEvent* _event);

private:
	// Определение местоположения курсора над виджетом
	CursorPosition cursorPosition(const QRectF& _cropRect, const QPointF& _mousePosition);
	// Обновить иконку курсора соответствующую местоположению мыши
	void updateCursorIcon(const QPointF& _mousePosition);

	// Получить размер виджета после его изменения мышью
	// --------
	// Контракты:
	// 1. Метод должен вызываться, только при зажатой кнопке мыши
	//    (т.е. при перемещении или изменении размера виджета)
	// --------
	// В случае неудачи возвращает null-прямоугольник
	const QRectF calculateGeometry(const QRectF& _sourceGeometry, const CursorPosition _cursorPosition, const QPointF& _mouseDelta);
	// Получить размер виджета после его изменения мышью
	// Метод изменяет виджет не сохраняя начальных пропорций сторон
	// ------
	// Контракты:
	// 1. Метод должен вызываться, только при зажатой кнопке мыши
	//    (т.е. при перемещении или изменении размера виджета)
	const QRectF calculateGeometryWithCustomProportions(const QRectF& _sourceGeometry, const CursorPosition _cursorPosition,
		const QPointF& _mouseDelta);
	// Получить размер виджета после его изменения мышью
	// Метод изменяет виджет сохраняя начальные пропорции сторон
	// ------
	// Контракты:
	// 1. Метод должен вызываться, только при зажатой кнопке мыши
	//    (т.е. при перемещении или изменении размера виджета)
	const QRectF calculateGeometryWithFixedProportions(const QRectF &_sourceGeometry, const CursorPosition _cursorPosition,
		const QPointF &_mouseDelta, const QSizeF &_deltas);

private:
	// Private data implementation
	ImageCropperPrivate* pimpl;
};
