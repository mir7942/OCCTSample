#pragma once

class COCCTSampleView;

class OperatorBase
{
public:
	OperatorBase();
	virtual ~OperatorBase();

	virtual void OnLButtonDblClk(COCCTSampleView * pView, UINT nFlags, CPoint point);
	virtual void OnLButtonDown(COCCTSampleView * pView, UINT nFlags, CPoint point);
	virtual void OnLButtonUp(COCCTSampleView * pView, UINT nFlags, CPoint point);
	virtual void OnMButtonDblClk(COCCTSampleView * pView, UINT nFlags, CPoint point);
	virtual void OnMButtonDown(COCCTSampleView * pView, UINT nFlags, CPoint point);
	virtual void OnMButtonUp(COCCTSampleView * pView, UINT nFlags, CPoint point);
	virtual void OnRButtonDblClk(COCCTSampleView * pView, UINT nFlags, CPoint point);
	virtual void OnRButtonDown(COCCTSampleView * pView, UINT nFlags, CPoint point);
	virtual void OnRButtonUp(COCCTSampleView * pView, UINT nFlags, CPoint point);
	virtual void OnMouseMove(COCCTSampleView * pView, UINT nFlags, CPoint point);
	virtual BOOL OnMouseWheel(COCCTSampleView * pView, UINT nFlags, short zDelta, CPoint pt);
};

