#include "..\..\e2dshape.h"

e2d::Shape::Shape()
	: _style(Style::Solid)
	, _fillColor(0x6090A0U)
	, _lineColor(0x78B7D0U)
	, _strokeWidth(2)
	, _strokeStyle(nullptr)
{
}

e2d::Shape::~Shape()
{
}

void e2d::Shape::onRender()
{
	auto pBrush = Renderer::getSolidColorBrush();
	pBrush->SetOpacity(_displayOpacity);

	switch (_style)
	{
	case Style::Fill:
	{
		pBrush->SetColor(_fillColor.toD2DColorF());
		this->_renderFill();

		pBrush->SetColor(_lineColor.toD2DColorF());
		this->_renderLine();
		break;
	}

	case Style::Round:
	{
		pBrush->SetColor(_lineColor.toD2DColorF());
		this->_renderLine();
		break;
	}

	case Style::Solid:
	{
		pBrush->SetColor(_fillColor.toD2DColorF());
		this->_renderFill();
		break;
	}

	default:
		break;
	}
}

e2d::Color e2d::Shape::getFillColor() const
{
	return _fillColor;
}

e2d::Color e2d::Shape::getLineColor() const
{
	return _lineColor;
}

double e2d::Shape::getStrokeWidth() const
{
	return _strokeWidth;
}

e2d::Shape::Style e2d::Shape::getStyle() const
{
	return _style;
}

void e2d::Shape::setFillColor(Color fillColor)
{
	_fillColor = fillColor;
}

void e2d::Shape::setLineColor(Color lineColor)
{
	_lineColor = lineColor;
}

void e2d::Shape::setStrokeWidth(double strokeWidth)
{
	_strokeWidth = float(strokeWidth) * 2;
}

void e2d::Shape::setStyle(Style style)
{
	_style = style;
}

void e2d::Shape::setLineJoin(LineJoin lineJoin)
{
	switch (lineJoin)
	{
	case LineJoin::Miter:
		_strokeStyle = Renderer::getMiterID2D1StrokeStyle();
		break;
	case LineJoin::Bevel:
		_strokeStyle = Renderer::getBevelID2D1StrokeStyle();
		break;
	case LineJoin::Round:
		_strokeStyle = Renderer::getRoundID2D1StrokeStyle();
		break;
	default:
		_strokeStyle = nullptr;
		break;
	}
}
