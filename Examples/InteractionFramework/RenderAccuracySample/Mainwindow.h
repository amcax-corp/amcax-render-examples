#pragma once
#include <QMainWindow>
#include <QWidget>
#include <AMCAXRender.h>

namespace Ui {
	class MainWindow;
}

class Mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	Mainwindow(QWidget* parent = nullptr);
	~Mainwindow();

private:
	Ui::MainWindow* ui = nullptr;

	std::shared_ptr<AMCAXRender::IRenderComponent> mRenderComponent;
	std::shared_ptr<AMCAXRender::CBasicRender> mRender;

private slots:
	void onDoubleSpinBoxValueChanged(double value);
};
