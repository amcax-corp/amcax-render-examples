#ifndef VisltDemo_h
#define VisltDemo_h

#include <QMainWindow>
#include <AMCAXRender.h>

namespace Ui {
	class MainWindow;
}

class VisltDemoWindow : public QMainWindow
{
	Q_OBJECT
public:
	// Constructor/Destructor
	explicit VisltDemoWindow(QWidget* parent = nullptr);
	virtual ~VisltDemoWindow();
public slots:
	void handleOpenFile();
private:
	// Designer form
	Ui::MainWindow* ui = nullptr;

	std::shared_ptr<AMCAXRender::CBasicRender> render;
};

#endif