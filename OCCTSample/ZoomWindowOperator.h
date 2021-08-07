#pragma once

#include <AIS_RubberBand.hxx>
#include "OperatorBase.h"

class ZoomWindowOperator : public OperatorBase
{
public:
	ZoomWindowOperator();
	~ZoomWindowOperator() override;

	void OnLButtonDown(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	void OnLButtonUp(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	void OnMouseMove(COCCTSampleView* pView, UINT nFlags, CPoint point) override;

protected:
	void DrawRectangle(COCCTSampleView* pView, int minX, int minY, int maxX, int maxY, bool toDraw);

private:
	bool m_isStarted;
	int m_oldX, m_oldY;
	Handle(AIS_RubberBand) m_rubberBand;
};

