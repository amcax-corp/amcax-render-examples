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

	//距离测量
	void CreateLinearDimensions();

	//角度测量
	void CreateAngleDimensions();
private:
	Ui::MainwindowClass ui;

	std::shared_ptr<AMCAXRender::IRenderComponent> mRenderComponent;
	std::shared_ptr<AMCAXRender::CBasicRender> mRender;
};
