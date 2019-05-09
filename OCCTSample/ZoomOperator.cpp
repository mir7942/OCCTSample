#include "stdafx.h"
#include <V3d_View.hxx>
#include "OCCTSampleView.h"
#include "ZoomOperator.h"


ZoomOperator::ZoomOperator()
	: m_isStarted(false)
{
}


ZoomOperator::~ZoomOperator()
{
}

void ZoomOperator::OnLButtonDown(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	m_isStarted = true;
	m_oldX = point.x;
	m_oldY = point.y;
}

void ZoomOperator::OnLButtonUp(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	m_isStarted = false;
}

void ZoomOperator::OnMouseMove(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	if (!m_isStarted)
		OperatorBase::OnMouseMove(pView, nFlags, point);
	else
	{
		// 화면을 확대/축소시킨다.
		pView->GetView()->Zoom(point.y, m_oldX, m_oldY, point.x);

		m_oldX = point.x;
		m_oldY = point.y;
	}
}