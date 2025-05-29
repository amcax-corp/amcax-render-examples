#include"common.h"

QString GetTypeName(AMCAXRender::PickType type)
{
	QString name;
	switch (type)
	{
	case AMCAXRender::PickType::unknown:
		name = "unknown";
		break;
	case AMCAXRender::PickType::vert:
	case AMCAXRender::PickType::point:
		name = "vert";
		break;
	case AMCAXRender::PickType::edge:
		name = "edge";
		break;
	case AMCAXRender::PickType::face:
		name = "face";
		break;
	case AMCAXRender::PickType::body:
	case AMCAXRender::PickType::all:

		name = "body";
		break;
	default:
		break;
	}
	return name;

}

AMCAX::ShapeType PickTypeToShapeType(AMCAXRender::PickType t)
{
	switch (t)
	{
	case AMCAXRender::PickType::vert:
		return AMCAX::ShapeType::Vertex;
	case AMCAXRender::PickType::point:
		break;
	case AMCAXRender::PickType::edge:
		return AMCAX::ShapeType::Edge;

	case AMCAXRender::PickType::face:
		return AMCAX::ShapeType::Face;

	case AMCAXRender::PickType::body:
	case AMCAXRender::PickType::all:
		return AMCAX::ShapeType::Shape;
	}

	return AMCAX::ShapeType::Shape;
}

AMCAX::TopoShape FindSubShape(const AMCAX::TopoShape& shape, AMCAX::ShapeType type, int subIdex) {

	AMCAX::IndexSet<AMCAX::TopoShape> sets;
	AMCAX::TopoExplorerTool::MapShapes(shape, type, sets);

	if (subIdex < sets.size()) {
		return sets[subIdex];
	}
	return AMCAX::TopoShape();
}