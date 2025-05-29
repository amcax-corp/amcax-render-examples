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

private:
	Ui::MainwindowClass ui;
	std::shared_ptr<AMCAXRender::Material> material;
	void onColorButtonClicked();
	void onAmbientSliderChanged(int value);
	void onDiffuseSliderChanged(int value);
	void onSpecularSliderChanged(int value);
	void onSpecularPowerSliderChanged(int value);

	void handleOpenFile();
	std::vector<AMCAXRender::EntityId> entityIds;
	std::shared_ptr<AMCAXRender::IRenderComponent> mRenderComponent;
	std::shared_ptr<AMCAXRender::CBasicRender> mRender;
};
