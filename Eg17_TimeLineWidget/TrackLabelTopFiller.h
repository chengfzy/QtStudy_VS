#pragma once

#include <QWidget>

class TrackLabelTopFiller : public QWidget
{
	Q_OBJECT

public:
	TrackLabelTopFiller(QWidget *parent = nullptr);
	~TrackLabelTopFiller();

protected:
	void paintEvent(QPaintEvent *event) override;
};
