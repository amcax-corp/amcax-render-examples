#pragma once

#include <QWidget>
#include <AMCAXRender.h>

class QColorDialog;

class Mainwindow : public QWidget
{
	Q_OBJECT

public:
	Mainwindow(QWidget* parent = nullptr);
	~Mainwindow();

	void mouseReleaseEvent(QMouseEvent* event) override;


private:
	QColorDialog* colorDialog;
	std::shared_ptr<AMCAXRender::IRenderComponent> mRenderComponent;
	std::shared_ptr<AMCAXRender::CBasicRender> mRender;
};
