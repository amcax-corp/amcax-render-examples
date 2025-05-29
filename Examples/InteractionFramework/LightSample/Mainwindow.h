#pragma once

#include <QWidget>
#include <AMCAXRender.h>

class QColorDialog;
class LightPropertyView;

class Mainwindow : public QWidget
{
	Q_OBJECT

public:
	Mainwindow(QWidget* parent = nullptr);
	~Mainwindow();

private:
	void CreateSphere();
	QColorDialog* colorDialog;
	std::shared_ptr<AMCAXRender::IRenderComponent> mRenderComponent;
	std::shared_ptr<AMCAXRender::CBasicRender> mRender;
	LightPropertyView* m_lightProperty;
};
