#pragma once

#include <QWidget>
#include "ui_Mainwindow.h"
#include <AMCAXRender.h>
class Mainwindow : public QWidget
{
	Q_OBJECT

public:
	Mainwindow(QWidget *parent = nullptr);
	~Mainwindow();

	void Create3DTexture();
	void Create2DTexture();
private:
	Ui::MainwindowClass ui;

	std::shared_ptr<AMCAXRender::IRenderComponent> mRenderComponent;
	std::shared_ptr<AMCAXRender::CBasicRender> mRender;
};
