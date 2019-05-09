#include "stdafx.h"
#include <V3d_View.hxx>
#include "OCCTSampleView.h"
#include "RotationOperator.h"


RotationOperator::RotationOperator()
	: m_isStarted(false)
{
}


RotationOperator::~RotationOperator()
{
}

void RotationOperator::OnLButtonDown(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	m_isStarted = true;
	// 회전을 시작한다.
	pView->GetView()->StartRotation(point.x, point.y, 0.4);
}

void RotationOperator::OnLButtonUp(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	m_isStarted = false;
}

void RotationOperator::OnMouseMove(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	if (!m_isStarted)
		OperatorBase::OnMouseMove(pView, nFlags, point);
	else
	{
		// 마우스가 움직일 때 마다 회전한다.
		pView->GetView()->Rotation(point.x, point.y);
	}
}