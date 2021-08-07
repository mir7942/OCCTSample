#pragma once

#include "OperatorBase.h"

class RotationOperator : public OperatorBase
{
public:
	RotationOperator();
	~RotationOperator() override;

	void OnLButtonDown(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	void OnLButtonUp(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	void OnMouseMove(COCCTSampleView* pView, UINT nFlags, CPoint point) override;

private:
	bool m_isStarted;
};

