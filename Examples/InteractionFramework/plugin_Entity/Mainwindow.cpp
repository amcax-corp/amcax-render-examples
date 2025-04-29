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



	AMCAXRender::CAXMeshInfo cube;
	cube.category = "SHAPE";
	cube.id = "cube";

	// 顶点坐标，每个面需要四个点，共24个点
	cube.points = {
		// 面1
		{0.0, 0.0, 0.0}, {10.0, 0.0, 0.0}, {10.0, 10.0, 0.0}, {0.0, 10.0, 0.0},
		// 面2
		{0.0, 0.0, 10.0}, {10.0, 0.0, 10.0}, {10.0, 10.0, 10.0}, {0.0, 10.0, 10.0},
		// 面3
		{0.0, 0.0, 0.0}, {10.0, 0.0, 0.0}, {10.0, 0.0, 10.0}, {0.0, 0.0, 10.0},
		// 面4
		{10.0, 10.0, 0.0}, {0.0, 10.0, 0.0}, {0.0, 10.0, 10.0}, {10.0, 10.0, 10.0},
		// 面5
		{0.0, 0.0, 0.0}, {0.0, 10.0, 0.0}, {0.0, 10.0, 10.0}, {0.0, 0.0, 10.0},
		// 面6
		{10.0, 0.0, 0.0}, {10.0, 10.0, 0.0}, {10.0, 10.0, 10.0}, {10.0, 0.0, 10.0}
	};

	// 法向量，每个面需要四个法向量，共24个法向量
	cube.normals = {
		// 面1
		{0.0, 0.0, -1.0}, {0.0, 0.0, -1.0}, {0.0, 0.0, -1.0}, {0.0, 0.0, -1.0},
		// 面2
		{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0},
		// 面3
		{0.0, -1.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, -1.0, 0.0},
		// 面4
		{0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0},
		// 面5
		{-1.0, 0.0, 0.0}, {-1.0, 0.0, 0.0}, {-1.0, 0.0, 0.0}, {-1.0, 0.0, 0.0},
		// 面6
		{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}
	};

	// 顶点数据
	//cube.vertex.topoType = "point";
	//cube.vertex.vertices = {
	//	0.0, 0.0, 0.0, 10.0, 0.0, 0.0, 10.0, 10.0, 0.0, 0.0, 10.0, 0.0,
	//	0.0, 0.0, 10.0, 10.0, 0.0, 10.0, 10.0, 10.0, 10.0, 0.0, 10.0, 10.0
	//};

	// 边数据
	//cube.edges = {
	//	{"index", {0, 1}}, {"index", {1, 2}}, {"index", {2, 3}}, {"index", {3, 0}},
	//	{"index", {4, 5}}, {"index", {5, 6}}, {"index", {6, 7}}, {"index", {7, 4}},
	//	{"index", {0, 4}}, {"index", {1, 5}}, {"index", {2, 6}}, {"index", {3, 7}}
	//};

	// 面数据
	cube.faces = {
		{{{0, 2, 1}, {0, 3, 2}}, {0, 1, 2, 3}, 4, {{0.0, 0.0, -1.0}}, {}},
		{{{4, 5, 6}, {4, 6, 7}}, {4, 5, 6, 7}, 4, {{0.0, 0.0, 1.0}}, {}},
		{{{8, 9, 10}, {8, 10, 11}}, {8, 9, 10, 11}, 4, {{0.0, -1.0, 0.0}}, {}},
		{{{12, 13, 14}, {12, 14, 15}}, {12, 13, 14, 15}, 4, {{0.0, 1.0, 0.0}}, {}},
		{{{16, 18, 17}, {16, 19, 18}}, {16, 17, 18, 19}, 4, {{-1.0, 0.0, 0.0}}, {}},
		{{{20, 21, 22}, {20, 22, 23}}, {20, 21, 22, 23}, 4, {{1.0, 0.0, 0.0}}, {}}
	};

	//构建实体数据
	auto entity = mRender->entityFactory->FromCAXMeshInfo(cube);

	//颜色表
	std::vector<double> scalars;
	std::map<double, std::vector<double>> colorMap;
	colorMap.emplace(0, std::vector<double>{ 0, 0, 0 });
	colorMap.emplace(1, std::vector<double>{ 1, 0, 0 });
	colorMap.emplace(2, std::vector<double>{ 1, 1, 0 });
	colorMap.emplace(3, std::vector<double>{ 1, 1, 1 });
	colorMap.emplace(4, std::vector<double>{ 0, 1, 1 });
	colorMap.emplace(5, std::vector<double>{ 0, 0, 1 });
	for (auto i = 0; i < 6; i++) {
		scalars.push_back(i);
	}

	//矩阵设置
	double matrix[4][4] = {
		1,0,0,-25,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1,
	};

	//创建Entity插件
	auto pId = mRender->pluginManage->AddPluginFromMeshEntity(entity);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::EntityPlugProp>(pId);
	
	att->SetColorMap(colorMap, scalars, AMCAXRender::ColorMapType::CellStepColorByCellScalar);
	att->SetOpacity(1);
	att->SetLineWidth(2);
	att->SetMatrix(*matrix);
	
	//设置插件属性
	mRender->pluginManage->SetProperty(pId, att);

	//设置高亮颜色
	double c[3] = { 1,0,1 };
	mRender->pluginManage->SetHightLightColor(c);

	//注册鼠标点击拾取插件
	mRender->pluginManage->RegisterPickEvent(AMCAXRender::EventType::mouse_click,
		[&](AMCAXRender::EntityId entityId, AMCAXRender::PickType type, int subIndex, double* worldPos) {
			
			//设置高亮
			mRender->pluginManage->ClearHightLight(entityId);
			mRender->pluginManage->AddHightLight(entityId, type, subIndex);

		}
	);


	//颜色图例设置
	double pos[] = { 0.9,0.1,0.1,0.8 };
	std::vector<std::vector<double>> colorList;
	colorList.push_back(std::vector<double>{ 0, 0, 0 });
	colorList.push_back(std::vector<double>{ 1, 0, 0 });
	colorList.push_back(std::vector<double>{ 1, 1, 0 });
	colorList.push_back(std::vector<double>{ 1, 1, 1 });
	colorList.push_back(std::vector<double>{ 0, 1, 1 });
	colorList.push_back(std::vector<double>{ 0, 0, 1 });
	std::vector<std::string> labels;
	labels.push_back("");
	labels.push_back("0");
	labels.push_back("1");
	labels.push_back("2");
	labels.push_back("3");
	labels.push_back("4");
	labels.push_back("5");
	mRender->styleManage->SetColorBarPosition(pos);
	mRender->styleManage->SetColorBarColorMap(colorList, labels);
	mRender->styleManage->SetColorBarVisible(1);


	//更新数据
	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();

}

Mainwindow::~Mainwindow()
{

}
