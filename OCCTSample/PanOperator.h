#pragma once

#include "OperatorBase.h"

class PanOperator : public OperatorBase
{
public:
	PanOperator();
	~PanOperator();

	virtual void OnLButtonDown(COCCTSampleView * pView, UINT nFlags, CPoint point) override;
	virtual void OnLButtonUp(COCCTSampleView * pView, UINT nFlags, CPoint point) override;
	virtual void OnMouseMove(COCCTSampleView * pView, UINT nFlags, CPoint point) override;

private:
	bool m_isStarted;
	int m_oldX, m_oldY;
};

