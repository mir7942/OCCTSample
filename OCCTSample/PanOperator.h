#pragma once
#include "OperatorBase.h"

class PanOperator : public OperatorBase
{
public:
	PanOperator();
	~PanOperator() override;

	void OnLButtonDown(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	void OnLButtonUp(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	void OnMouseMove(COCCTSampleView* pView, UINT nFlags, CPoint point) override;

private:
	bool m_isStarted;
	int m_oldX, m_oldY;
};


