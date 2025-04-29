#include "Mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//初始化
	mRenderComponent = AMCAXRender::CreateRenderComponent(this);
	mRender = mRenderComponent->CreateBasicRender();

	//窗口布局
	ui.gridLayout->addWidget(mRender->widget);

	//创建多个箭头
	auto id = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kArrow);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::ArrowProp>(id);

	//构造箭头数据，位置，方向，颜色设置
	for (int i = 0; i < 10; i++) {
		std::vector<double> pos = { (double)(rand() % 10) , (double)(rand() % 10) , (double)(rand() % 10) };
		std::vector<double> color = { (double)(rand() % 255) / 255.0 , (double)(rand() % 255) / 255.0 , (double)(rand() % 255) / 255.0 };
		std::vector<double> dir = { (double)(rand()),(double)(rand()),(double)(rand()) };
		att->AddArrow(pos, dir, color, rand() % 10);
	}
	//是否顶层显示
	att->SetTopRender(false);
	mRender->pluginManage->SetProperty(id, att);
	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
