#include "MWindow.h"

#include<QDateTime>

MWindow::MWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//初始化
	mRenderComponent = AMCAXRender::CreateRenderComponent(this);
	mRender = mRenderComponent->CreateBasicRender();

	//窗口布局
	ui.gridLayout->addWidget(mRender->widget);

	//加载模型
	LoadModel();

	dlgDistance = new DlgMeasurement(mRender,this);
	
	mActGroup = new QActionGroup(this);
	ui.actionDistanceMeasure->setData(DlgMeasurement::kDistance);
	ui.actionLenghtMeasure  ->setData(DlgMeasurement::kLength);
	ui.actionSquareMeasure  ->setData(DlgMeasurement::kSquare);
	ui.actionAngleMeasure   ->setData(DlgMeasurement::kAngle);
	ui.actionVolumeMeasure  ->setData(DlgMeasurement::kVolume);
	mActGroup->addAction(ui.actionDistanceMeasure);
	mActGroup->addAction(ui.actionLenghtMeasure);
	mActGroup->addAction(ui.actionSquareMeasure);
	mActGroup->addAction(ui.actionAngleMeasure);
	mActGroup->addAction(ui.actionVolumeMeasure );
	
	connect(mActGroup, &QActionGroup::triggered, this, [this](QAction* act) {
		DlgMeasurement::MeasureType type =(DlgMeasurement::MeasureType)qobject_cast<QAction*>(act)->data().toInt();
		dlgDistance->showPage(type);

		});
}

MWindow::~MWindow()
{}

void MWindow::LoadModel()
{
	//创建立方体
	AMCAX::TopoShape cube = AMCAX::MakeBox(10.0, 10.0, 10.0);
	auto cubeEntity = mRender->entityFactory->FromShape(cube);
	mRender->entityManage->AddEntity(cubeEntity);
	mShapsSet[cubeEntity->GetEntityId()] = cube;

	//创建圆柱
	AMCAX::Frame3 frame(AMCAX::Point3(20., 0., 0.), AMCAX::Direction3(1.0, 0.0, 1.0));
	double radius = 2.0;
	double height = 5.0;
	auto cylinder = AMCAX::MakeCylinder(frame, radius, height).Shape();
	auto cylinderEntity = mRender->entityFactory->FromShape(cylinder);
	mRender->entityManage->AddEntity(cylinderEntity);
	mShapsSet[cylinderEntity->GetEntityId()] = cylinder;


	//刷新渲染
	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

void MWindow::logMessage(const QString& message)
{
	QDateTime currentTime = QDateTime::currentDateTime();
	QString timestamp = currentTime.toString("yyyy-MM-dd HH:mm:ss");
	ui.textEdit->append(QString("[%1] %2").arg(timestamp, message));
}
