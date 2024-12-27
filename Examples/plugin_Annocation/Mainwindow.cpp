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


	//创建标注
	//构造线数据
	std::vector <AMCAXRender::Line3D> lines;
	lines.push_back({ { 20,0,0 }, { -20,0,0 } });

	//构造偏移线段，（线段两端固定像素偏移）
	std::vector <AMCAXRender::Line3D> offsetLines;
	offsetLines.push_back({ {20,0,0}, { 20,0,10 } });
	offsetLines.push_back({ {-20,0,0}, { -20,0,10 } });
	std::vector<std::tuple<double, double>> offsetPad;
	offsetPad.push_back({ 20,10 });
	offsetPad.push_back({ 20,10 });

	//构造箭头对
	std::vector<AMCAXRender::Point3D> arrowPairs;
	arrowPairs.push_back({ 20,0,0 });
	arrowPairs.push_back({-20,0,0 });
	//箭头方向
	std::vector<AMCAXRender::Point3D> arrowPairsDirection;
	arrowPairsDirection.push_back({ std::get<0>(arrowPairs[0]) - std::get<0>(arrowPairs[1]),std::get<1>(arrowPairs[0])- std::get<1>(arrowPairs[1]), std::get<2>(arrowPairs[0])- std::get<2>(arrowPairs[1]) });
	arrowPairsDirection.push_back({ std::get<0>(arrowPairs[1]) - std::get<0>(arrowPairs[0]),std::get<1>(arrowPairs[1]) - std::get<1>(arrowPairs[0]), std::get<2>(arrowPairs[1]) - std::get<2>(arrowPairs[0]) });

	//构造标注文本
	std::vector<AMCAXRender::Point3D> labels;
	labels.push_back({0,0,0});
	std::vector<std::wstring> labelsText;
	labelsText.push_back(L"标注文本");

	auto id  = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kDistance);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::DistanceProp>(id);

	att->SetLines({lines});
	att->SetOffsetLines(offsetLines, offsetPad);
	att->SetArrowPairs(arrowPairs, arrowPairsDirection);
	att->SetLabels(labels, labelsText);

	mRender->pluginManage->SetProperty(id, att);
	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
