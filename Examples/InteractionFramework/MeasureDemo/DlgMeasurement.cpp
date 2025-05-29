#include "DlgMeasurement.h"
#include "MWindow.h"

#include <topology/BRepExtremaDistShapeShape.hpp>

#include <nurbs/NURBSAPIGetGeometry.hpp>
#include <geometry/ComputePointsAbscissa.hpp>

#include <topology/BRepGlobalProperty.hpp>
#include <geometry/GlobalProperty.hpp>
#include <topology/TopoTool.hpp>

DlgMeasurement::DlgMeasurement(std::shared_ptr<AMCAXRender::CBasicRender> render, MWindow* parent)
	: QDialog(parent)
	, mRender(render)
	, minWindow(parent)
{
	ui.setupUi(this);

	this->setFocusPolicy(Qt::FocusPolicy::NoFocus);

	mRender->interactionCenter->RegisterPickEvent(AMCAXRender::EventType::mouse_click,
		[&](AMCAXRender::EntityId parentId, AMCAXRender::EntityId entityId, AMCAXRender::PickType type, int subIndex, int* pos) {
			
			PickInfo currentPickInfo = { entityId ,type,subIndex };

			if (ui.pushButton->isChecked()) {
				if (currentPickInfo.type != AMCAXRender::PickType::unknown) {
				
					mRender->entityManage->RemoveHightLight(mPickInf[0].entityId, mPickInf[0].type, mPickInf[0].subIndex);

					mPickInf[0] = currentPickInfo;
					ui.pushButton->setText(mPickInf[0].GetMessage());
					mRender->entityManage->AddHightLight(mPickInf[0].entityId, mPickInf[0].type, mPickInf[0].subIndex);
					ui.pushButton->setChecked(false);
				}
		
			}

			if (ui.pushButton_2->isChecked()) {
				if (currentPickInfo.type != AMCAXRender::PickType::unknown) {
					mRender->entityManage->RemoveHightLight(mPickInf[1].entityId, mPickInf[1].type, mPickInf[1].subIndex);

					mPickInf[1] = currentPickInfo;
					ui.pushButton_2->setText(mPickInf[1].GetMessage());
					mRender->entityManage->AddHightLight(mPickInf[1].entityId, mPickInf[1].type, mPickInf[1].subIndex);
					ui.pushButton_2->setChecked(false);
				}
			}
		}

	);

	connect(ui.pushButton_3, &QPushButton::clicked, this, [this]() {
		switch (mCurrentType)
		{
		case DlgMeasurement::kDistance:
			calcDistance();
			break;
		case DlgMeasurement::kLength:
			calcLength();
			break;
		case DlgMeasurement::kSquare:
			calcSquare();
			break;
		case DlgMeasurement::kAngle:
			calcAngle();
			break;
		case DlgMeasurement::kVolume:
			calcVolume();
			break;
		default:
			break;
		}
		
	});
}

DlgMeasurement::~DlgMeasurement()
{}

void DlgMeasurement::showPage(MeasureType t)
{
	switch (t)
	{
	case DlgMeasurement::kDistance:
		ui.widget->setVisible(true);
		ui.widget_2->setVisible(true);
		this->setWindowTitle("距离测量");

		mRender->interactionCenter->PickEventFilter(AMCAXRender::PickType::body);
		break;
	case DlgMeasurement::kLength:
		ui.widget->setVisible(true);
		ui.widget_2->setVisible(false);
		this->setWindowTitle(("长度测量"));
		mRender->interactionCenter->PickEventFilter(AMCAXRender::PickType::edge);

		break;
	case DlgMeasurement::kSquare:		
		ui.widget->setVisible(true);
		ui.widget_2->setVisible(false);
		this->setWindowTitle(("面积测量"));
		mRender->interactionCenter->PickEventFilter(AMCAXRender::PickType::face);

		break;
	case DlgMeasurement::kAngle:
		ui.widget->setVisible(true);
		ui.widget_2->setVisible(true);
		this->setWindowTitle(("角度测量"));
		mRender->interactionCenter->PickEventFilter(AMCAXRender::PickType::edge);

		break;
	case DlgMeasurement::kVolume:
		ui.widget->setVisible(true);
		ui.widget_2->setVisible(false);
		this->setWindowTitle(("体积测量"));
		mRender->interactionCenter->PickEventFilter(AMCAXRender::PickType::all);

		break;
	default:
		break;
	}
	mCurrentType = t;

	clearData();
	show();
}

void DlgMeasurement::closeEvent(QCloseEvent* event)
{
	QDialog::closeEvent(event);

	clearData();
	mRender->interactionCenter->PickEventFilter(AMCAXRender::PickType::body);

}

void DlgMeasurement::clearData()
{
	mRender->entityManage->ClearHightLight();
	mRender->entityManage->DoRepaint();
	
	ui.label_3->clear();

	ui.pushButton->setText("拾取");
	ui.pushButton_2->setText("拾取");

	ui.buttonGroup->setExclusive(false);
	ui.pushButton->setChecked(false);
	ui.pushButton_2->setChecked(false);
	ui.buttonGroup->setExclusive(true);

}

void DlgMeasurement::calcDistance()
{
	auto shape1 = FindSubShape(minWindow->FindToposhaeById(mPickInf[0].entityId), PickTypeToShapeType(mPickInf[0].type), mPickInf[0].subIndex);
	auto shape2 = FindSubShape(minWindow->FindToposhaeById(mPickInf[1].entityId), PickTypeToShapeType(mPickInf[1].type), mPickInf[1].subIndex);

	if (shape1.IsNull() || shape2.IsNull()) {
		return ;
	}
	//计算距离
	AMCAX::BRepExtremaDistShapeShape compute(shape1, shape2);
	if (compute.Perform()) {

		//获取距离
		double dist = compute.Value();

		//计算分量
		auto point1 = compute.PointOnShape1(0);
		auto point2 = compute.PointOnShape2(0);

		AMCAX::Vector3 v_1(point1, point2);
		auto x = std::abs(v_1.X());
		auto y = std::abs(v_1.Y());
		auto z = std::abs(v_1.Z());


		auto text = QString("distance : %1 \nx : %2 \ny : %3 \nz : %4 \n")
			.arg(QString::number(/*v_1.Norm()*/dist))
			.arg(QString::number(x))
			.arg(QString::number(y))
			.arg(QString::number(z));

		ui.label_3->setText(text);
	}

}

void DlgMeasurement::calcLength()
{
	//长度测量
	auto shape1 = FindSubShape(minWindow->FindToposhaeById(mPickInf[0].entityId), PickTypeToShapeType(mPickInf[0].type), mPickInf[0].subIndex);
	if (shape1.IsNull() ) {
		return ;
	}
	auto edge = static_cast<const AMCAX::TopoEdge&>(shape1);
	auto curve3 = AMCAX::NURBSAPIGetGeometry::GetCurve(edge);
	AMCAX::AdaptorGeom3Curve adaptor(curve3);
	AMCAX::ComputePointsAbscissa compute1(adaptor, 0.001, curve3->FirstParameter());
	double length = compute1.Length(adaptor);

	ui.label_3->setText(QString::number( length));
}

void DlgMeasurement::calcSquare()
{
	//面积测量
	auto shape1 = FindSubShape(minWindow->FindToposhaeById(mPickInf[0].entityId), PickTypeToShapeType(mPickInf[0].type), mPickInf[0].subIndex);

	if (shape1.IsNull()) {
		return ;
	}

	AMCAX::GlobalProperty prop;
	AMCAX::BRepGlobalProperty::SurfaceProperties(shape1, prop);
	auto v = prop.Mass();
	ui.label_3->setText(QString::number(v));

}
void DlgMeasurement::calcAngle()
{
	auto edge1 = static_cast<const AMCAX::TopoEdge&>(FindSubShape(minWindow->FindToposhaeById(mPickInf[0].entityId), PickTypeToShapeType(mPickInf[0].type), mPickInf[0].subIndex));
	auto edge2 = static_cast<const AMCAX::TopoEdge&>(FindSubShape(minWindow->FindToposhaeById(mPickInf[1].entityId), PickTypeToShapeType(mPickInf[1].type), mPickInf[1].subIndex));
	if (edge1.IsNull() || edge2.IsNull()) {
		return ;
	}


	//判断是否是直线
	double f, l;
	auto flag1 = AMCAX::TopoTool::Curve(edge1, f, l)->Type() != AMCAX::CurveType::Line;
	auto flag2 = AMCAX::TopoTool::Curve(edge2, f, l)->Type() != AMCAX::CurveType::Line;

	if (flag1 || flag2) {
		return;
	}

	//获取line1的向量
	AMCAX::TopoVertex vfirst;
	AMCAX::TopoVertex vlast;
	AMCAX::TopoExplorerTool::Vertices(edge1, vfirst, vlast);

	AMCAX::Point3 pt1 = AMCAX::TopoTool::Point(vfirst);
	AMCAX::Point3 pt2 = AMCAX::TopoTool::Point(vlast);
	AMCAX::Vector3 v_1(pt1,pt2);
	v_1.Normalize();

	//获取line2的向量
	AMCAX::TopoVertex vfirst2;
	AMCAX::TopoVertex vlast2;
	AMCAX::TopoExplorerTool::Vertices(edge2, vfirst2, vlast2);

	AMCAX::Point3 pt3 = AMCAX::TopoTool::Point(vfirst2);
	AMCAX::Point3 pt4 = AMCAX::TopoTool::Point(vlast2);
	AMCAX::Vector3 v_2(pt3, pt4);
	v_2.Normalize();

	//计算角度
	auto angle = v_1.Angle(v_2) * 180.0 / M_PI;
	ui.label_3->setText(QString::number(angle));

}

void DlgMeasurement::calcVolume()
{
	auto shape1 = minWindow->FindToposhaeById(mPickInf[0].entityId);
	if (shape1.IsNull()) {
		return ;
	}
	//体积测量
	AMCAX::GlobalProperty prop;
	AMCAX::BRepGlobalProperty::VolumeProperties(shape1, prop);
	auto v = prop.Mass();

	ui.label_3->setText(QString::number(v));

}

