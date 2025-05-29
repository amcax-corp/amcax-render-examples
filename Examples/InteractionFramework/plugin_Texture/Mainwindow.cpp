#include "Mainwindow.h"
#include<iostream>

#include <topology/TopoFace.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoEdge.hpp>
#include <topology/TopoTool.hpp>
#include <geometry/MakeCircle2.hpp>
#include <geometry/MakeEllipse2.hpp>
#include <modeling/MakeCylinder.hpp>
#include <modeling/MakeEdge.hpp>
#include <geometry/MakeGeom2Circle.hpp>
#include <modeling/MakeBox.hpp>
#include <topology/BRepAdaptorSurface.hpp>

Mainwindow::Mainwindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//初始化
	mRenderComponent = AMCAXRender::CreateRenderComponent(this);
	mRender = mRenderComponent->CreateBasicRender();

	//窗口布局
	ui.gridLayout->addWidget(mRender->widget);

	connect(ui.pushButton_2d, &QPushButton::clicked, this, &Mainwindow::Create2DTexture);
	connect(ui.pushButton_3d, &QPushButton::clicked, this, &Mainwindow::Create3DTexture);

}

Mainwindow::~Mainwindow()
{

}

void Mainwindow::Create3DTexture()
{
	auto F_ConstructTexureData = [](AMCAX::BRepAdaptorSurface surface, double u, double v, AMCAXRender::TextureProp3D::TextureData& data) {

		AMCAX::Point3 point;
		AMCAX::Vector3 du, dv, nomal;
		surface.D1(u, v, point, du, dv);
		nomal = du.Cross(dv);

		data.points.insert(data.points.end(), { point.X(),point.Y(),point.Z() });
		data.normals.insert(data.normals.end(), { nomal.X(),nomal.Y(),nomal.Z() });
		data.colors.insert(data.colors.end(), { (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), 0 });
		//data.scales.insert(data.scales.end(),{1,0.2,0.5});
		data.angles.insert(data.angles.end(), { 45 });

		};

	AMCAX::TopoShape model;//模型
	AMCAX::TopoFace ReferenceFace;//参考面
	AMCAX::TopoShape shape;//纹理

#if 1
	//创建圆柱
	AMCAX::Frame3 frame(AMCAX::Point3(0., 0., 0.), AMCAX::Direction3(0.0, 0.0, 1.0));
	double radius = 2.0;
	double height = 5.0;
	AMCAX::MakeCylinder mkCylinder = AMCAX::MakeCylinder(frame, radius, height);
	//获得圆柱体的 侧面
	ReferenceFace = mkCylinder.Face();
	model = static_cast<const AMCAX::TopoShape&>(ReferenceFace);
#else
	//创建立方体
	model = AMCAX::MakeBox(10, 10, 10);
	AMCAX::IndexSet<AMCAX::TopoShape> shapeFaces_;
	AMCAX::TopoExplorerTool::MapShapes(model, AMCAX::ShapeType::Face, shapeFaces_);
	ReferenceFace = static_cast<const AMCAX::TopoFace&>(shapeFaces_[1]);
#endif

	//渲染模型
	mRender->entityManage->AddEntity(mRender->entityFactory->FromShape(model));

	//3d纹理
	shape = AMCAX::MakeBox(0.1, 0.1, 0.1);


	//获取uv范围
	AMCAX::BRepAdaptorSurface adapt(ReferenceFace);
	double uFirst = adapt.FirstUParameter();
	double uLast = adapt.LastUParameter();
	double vFirst = adapt.FirstVParameter();
	double vLast = adapt.LastVParameter();

	auto entity = mRender->entityFactory->FromShape(shape);
	auto id = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kTextureProp);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::TextureProp3D>(id);

	//纹理属性设置
	AMCAXRender::TextureProp3D::TextureData data;
	int size = 20;
	int size2 = 20;

	auto ustep = (uLast - uFirst) / size;
	auto vstep = (vLast - vFirst) / size2;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size2; j++) {
			F_ConstructTexureData(adapt, uFirst + i * ustep, vFirst + j * vstep, data);
		}
	}

	att->CreateTexture(entity, data);

	mRender->pluginManage->SetProperty(id, att);
	mRender->entityManage->DoRepaint();
	mRender->cameraManage->ResetCamera();
}

void Mainwindow::Create2DTexture()
{
	AMCAX::TopoShape model;//模型
	AMCAX::TopoFace ReferenceFace;//参考面
	AMCAX::TopoShape shape;//纹理

	//创建立方体
	model = AMCAX::MakeBox(10, 10, 10);
	AMCAX::IndexSet<AMCAX::TopoShape> shapeFaces_;
	AMCAX::TopoExplorerTool::MapShapes(model, AMCAX::ShapeType::Face, shapeFaces_);
	ReferenceFace = static_cast<const AMCAX::TopoFace&>(shapeFaces_[1]);

	//渲染模型
	mRender->entityManage->AddEntity(mRender->entityFactory->FromShape(model));


	//获取uv范围
	AMCAX::BRepAdaptorSurface adapt(ReferenceFace);
	double uFirst = adapt.FirstUParameter();
	double uLast = adapt.LastUParameter();
	double vFirst = adapt.FirstVParameter();
	double vLast = adapt.LastVParameter();

	auto entity = mRender->entityFactory->FromShape(shape);
	auto id = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kTexture2D);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::TextureProp2D>(id);

	//矩形纹理
	auto rect = std::make_shared<AMCAXRender::TextureProp2D::RectShape>();
	rect->w = 0.5;
	rect->h = 0.5;

	//圆
	auto circle = std::make_shared<AMCAXRender::TextureProp2D::CircleShape>();
	circle->radius = 0.02;

	//椭圆纹理，注意椭圆的长轴必须大于短轴
	auto ellipse = std::make_shared<AMCAXRender::TextureProp2D::EllipseShape>();
	ellipse->d = { 1,0 };
	ellipse->majorRadius = 0.315;
	ellipse->minorRadius = 3.1415926 / 180 * 18;

	//纹理属性设置
	AMCAXRender::TextureProp2D::TextureData data;
	data.shape = rect;
	//data.shape = circle;
	//data.shape = ellipse;

	int size = 5;
	int size2 = 5;

	auto ustep = (uLast - uFirst) / size;
	auto vstep = (vLast - vFirst) / size2;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size2 + 0; j++) {
			//纹理坐标
			data.uvPos.push_back({ uFirst + i * ustep ,vFirst + j * vstep });

			//颜色
			data.colors.push_back({ (rand() % 255) ,(rand() % 255),0 });

			//缩放
			data.scales.push_back({ 2.0 ,1.5 });

			//自旋
			data.angle.push_back(45.0);
		}
	}

	att->SetTranslate(0, 5, 5);
	att->SetRotateWXYZ(45, 1, 0, 0);
	att->SetTranslate(0, -5, -5);

	att->CreateTexture(ReferenceFace, data);

	//生成圆形裁剪区域
	{
		std::vector<AMCAX::TopoEdge> region;

		//构建圆
		AMCAX::Point2 center(5.0, -5.0);//u, v
		double cRadius = 5.0;//v
		AMCAX::Circle2 circle2 = AMCAX::MakeCircle2(center, cRadius);
		auto theCurve = AMCAX::MakeGeom2Circle(circle2).Value();
		std::shared_ptr<AMCAX::Geom3Surface> cySurface = AMCAX::TopoTool::Surface(ReferenceFace);
		AMCAX::TopoEdge edge = AMCAX::MakeEdge(theCurve, cySurface);

		region.push_back(edge);

		att->ClipByRegion(region);

		//显示裁剪线框
		att->SetClipToolsVisible(1);
	}

	//获取与边界相交的纹理id
	std::vector<uint32_t> interIds;
	std::vector<uint32_t> insideIds;
	std::vector<uint32_t> outsideIds;
	att->GetIntersectionIds(interIds, insideIds, outsideIds);
	std::cout << "insideCount : " << insideIds.size() << " outsideCount : " << outsideIds.size() << " interCount : " << interIds.size() << std::endl;


	mRender->pluginManage->SetProperty(id, att);
	mRender->entityManage->DoRepaint();
	mRender->cameraManage->ResetCamera();

}
