#include "stdafx.h"

#include <V3d_View.hxx>

#include "OCCTSampleView.h"
#include "PanOperator.h"


PanOperator::PanOperator()
	: m_isStarted(false)
{
}

PanOperator::~PanOperator()
{
}

void PanOperator::OnLButtonDown(COCCTSampleView* pView, UINT nFlags, CPoint point)
{
	m_isStarted = true;
	m_oldX = point.x;
	m_oldY = point.y;
}

void PanOperator::OnLButtonUp(COCCTSampleView* pView, UINT nFlags, CPoint point)
{
	m_isStarted = false;
}

void PanOperator::OnMouseMove(COCCTSampleView* pView, UINT nFlags, CPoint point)
{
	if (!m_isStarted)
		OperatorBase::OnMouseMove(pView, nFlags, point);
	else
	{
		// 이동량을 계산한다.
		int deltaX = point.x - m_oldX;
		int deltaY = m_oldY - point.y;
		// 카메라를 이동시킨다.
		pView->GetView()->Pan(deltaX, deltaY);

		m_oldX = point.x;
		m_oldY = point.y;
	}
}