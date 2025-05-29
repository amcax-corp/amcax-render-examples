#pragma once
#include <AMCAXRender.h>



#include <modeling/MakeShapeTool.hpp>
#include <topology/TopoFace.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoEdge.hpp>
#include <topology/TopoTool.hpp>
#include <geometry/MakeCircle2.hpp>
#include <geometry/MakeEllipse2.hpp>
#include <modeling/MakeCylinder.hpp>
#include <modeling/MakeEdge.hpp>
#include <geometry/MakeGeom2Circle.hpp>
#include <geometry/MakeGeom2Ellipse.hpp>
#include <geometry/Geom3Surface.hpp>

#include <modeling/MakeShapeTool.hpp>
#include <modeling/MakeBox.hpp>
#include <topology/TopoFace.hpp>
#include <topology/TopoCast.hpp>
#include <topology/TopoExplorerTool.hpp>
#include <topology/TopoTool.hpp>
#include <topology/TopoVertex.hpp>
#include <topology/TopoEdge.hpp>
#include <modeling/CopyShape.hpp>
#include <common/CoordT.hpp>
#include <common/TransformationType.hpp>
#include <common/Precision.hpp>
#include <math/TriangularMesh.hpp>
#include <math/PolygonOnTriangularMesh.hpp>
#include <math/Polygon3.hpp>
#include <topology/BRepBoundingBox.hpp>
#include <topomesh/BRepMeshIncrementalMesh.hpp>
#include <topology/BRepAdaptorCurve3.hpp>
#include <geometry/ComputePointsTangentialDeflection.hpp>
#include <topology/TopoShape.hpp>
#include <io/OBJTool.hpp>
#include <geometry/Geom3Curve.hpp>
#include <intersect/BRepIntCurveSurface.hpp>
#include <boolean/BoolBRepCut.hpp>
#include <geometry/Geom2TrimmedCurve.hpp>
#include <geometry/MakeSegment2d.hpp>
#include <step/StepData.hpp>
#include <step/StepDataTool.hpp>
#include <modeling/MakeBox.hpp>
#include <modeling/MakeCylinder.hpp>
#include <modeling/MakeSphere.hpp>
#include <modeling/MakeVertex.hpp>
#include <modeling/MakePolygon.hpp>
#include <modeling/TransformShape.hpp>
#include <topology/TopoFace.hpp>
#include <topology/BRepAdaptorSurface.hpp>
#include <occtio/OCCTTool.hpp>

#include<qstring.h>

QString GetTypeName(AMCAXRender::PickType type);

struct PickInfo
{
	AMCAXRender::EntityId entityId;
	AMCAXRender::PickType type;
	int subIndex = 0;

	QString GetMessage() {	
		return QString("%1 : %2").arg(GetTypeName(type)).arg(QString::number(subIndex));
	}
};

AMCAX::ShapeType PickTypeToShapeType(AMCAXRender::PickType t);

AMCAX::TopoShape FindSubShape(const AMCAX::TopoShape& shape, AMCAX::ShapeType type, int subIdex);