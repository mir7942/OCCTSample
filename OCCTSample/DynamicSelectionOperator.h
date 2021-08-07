#pragma once

#include "OperatorBase.h"

class SelectionOperator;
class PanOperator;
class RotationOperator;
class ZoomOperator;

class DynamicSelectionOperator : public OperatorBase
{
	enum class State
	{
		Selection,
		Panning,
		Rotation,
		Zoom
	};

public:
	DynamicSelectionOperator();
	~DynamicSelectionOperator() override;

	void OnLButtonDown(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	void OnLButtonUp(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	void OnMButtonDown(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	void OnMButtonUp(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	void OnMouseMove(COCCTSampleView* pView, UINT nFlags, CPoint point) override;
	BOOL OnMouseWheel(COCCTSampleView* pView, UINT nFlags, short zDelta, CPoint pt) override;

private:
	State m_state;

	SelectionOperator* m_pSelectionOperator;
	PanOperator* m_pPanOperator;
	RotationOperator* m_pRotationOperator;
	ZoomOperator* m_pZoomOperator;
};