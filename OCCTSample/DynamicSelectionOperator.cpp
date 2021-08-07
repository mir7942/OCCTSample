#include "stdafx.h"
#include <V3d_View.hxx>
#include "SelectionOperator.h"
#include "PanOperator.h"
#include "RotationOperator.h"
#include "ZoomOperator.h"
#include "OCCTSampleView.h"
#include "DynamicSelectionOperator.h"

DynamicSelectionOperator::DynamicSelectionOperator()
	: m_state(DynamicSelectionOperator::State::Selection)
	, m_pSelectionOperator(new SelectionOperator())
	, m_pPanOperator(new PanOperator())
	, m_pRotationOperator(new RotationOperator())
	, m_pZoomOperator(new ZoomOperator())
{

}

DynamicSelectionOperator::~DynamicSelectionOperator()
{
	delete m_pZoomOperator;
	delete m_pRotationOperator;
	delete m_pPanOperator;
	delete m_pSelectionOperator;
}

void DynamicSelectionOperator::OnLButtonDown(COCCTSampleView* pView, UINT nFlags, CPoint point)
{
	switch (m_state)
	{
	case State::Selection:
		m_pSelectionOperator->OnLButtonDown(pView, nFlags, point);
		break;
	default:
		OperatorBase::OnLButtonDown(pView, nFlags, point);
		break;
	}
}

void DynamicSelectionOperator::OnLButtonUp(COCCTSampleView* pView, UINT nFlags, CPoint point)
{
	switch (m_state)
	{
	case State::Selection:
		m_pSelectionOperator->OnLButtonUp(pView, nFlags, point);
		break;
	default:
		OperatorBase::OnLButtonUp(pView, nFlags, point);
		break;
	}
}

void DynamicSelectionOperator::OnMButtonDown(COCCTSampleView* pView, UINT nFlags, CPoint point)
{
	switch (m_state)
	{
	case State::Selection:
		if (!(nFlags & MK_CONTROL) && !(nFlags & MK_SHIFT))
		{
			m_pRotationOperator->OnLButtonDown(pView, nFlags, point);
			m_state = State::Rotation;
		}
		else if ((nFlags & MK_CONTROL) && !(nFlags & MK_SHIFT))
		{
			m_pPanOperator->OnLButtonDown(pView, nFlags, point);
			m_state = State::Panning;
		}
		else if (!(nFlags & MK_CONTROL) && (nFlags & MK_SHIFT))
		{
			m_pZoomOperator->OnLButtonDown(pView, nFlags, point);
			m_state = State::Zoom;
		}
		break;
	default:
		OperatorBase::OnMButtonDown(pView, nFlags, point);
		break;
	}
}

void DynamicSelectionOperator::OnMButtonUp(COCCTSampleView* pView, UINT nFlags, CPoint point)
{
	switch (m_state)
	{
	case State::Rotation:
		m_pRotationOperator->OnLButtonUp(pView, nFlags, point);
		m_state = State::Selection;
		break;
	case State::Panning:
		m_pPanOperator->OnLButtonUp(pView, nFlags, point);
		m_state = State::Selection;
		break;
	case State::Zoom:
		m_pZoomOperator->OnLButtonUp(pView, nFlags, point);
		m_state = State::Selection;
		break;
	default:
		OperatorBase::OnMButtonDown(pView, nFlags, point);
		break;
	}
}

void DynamicSelectionOperator::OnMouseMove(COCCTSampleView* pView, UINT nFlags, CPoint point)
{
	switch (m_state)
	{
	case State::Selection:
		m_pSelectionOperator->OnMouseMove(pView, nFlags, point);
		break;
	case State::Rotation:
		m_pRotationOperator->OnMouseMove(pView, nFlags, point);
		break;
	case State::Panning:
		m_pPanOperator->OnMouseMove(pView, nFlags, point);
		break;
	case State::Zoom:
		m_pZoomOperator->OnMouseMove(pView, nFlags, point);
		break;
	default:
		OperatorBase::OnMouseMove(pView, nFlags, point);
		break;
	}
}

BOOL DynamicSelectionOperator::OnMouseWheel(COCCTSampleView* pView, UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0)
	{
		pView->GetView()->SetZoom(0.5);
	}
	else if (zDelta < 0)
	{
		pView->GetView()->SetZoom(2.0);
	}

	return TRUE;
}