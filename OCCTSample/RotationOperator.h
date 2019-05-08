#pragma once

#include "OperatorBase.h"

class RotationOperator : public OperatorBase
{
public:
	RotationOperator();
	~RotationOperator();

	virtual void OnLButtonDown(COCCTSampleView * pView, UINT nFlags, CPoint point) override;
	virtual void OnLButtonUp(COCCTSampleView * pView, UINT nFlags, CPoint point) override;
	virtual void OnMouseMove(COCCTSampleView * pView, UINT nFlags, CPoint point) override;

private:
	bool m_isStarted;
};

