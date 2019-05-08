#include "stdafx.h"
#include <V3d_View.hxx>
#include <AIS_InteractiveContext.hxx>
#include "OCCTSampleDoc.h"
#include "OCCTSampleView.h"
#include "SelectionOperator.h"


SelectionOperator::SelectionOperator()
	: m_isStarted(false)
{
	m_rubberBand = new AIS_RubberBand();
}


SelectionOperator::~SelectionOperator()
{
}

void SelectionOperator::OnLButtonDown(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	m_isStarted = true;
	m_oldX = point.x;
	m_oldY = point.y;
}

void SelectionOperator::OnLButtonUp(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	const int MinimumSize = 2;

	DrawRectangle(pView, m_oldX, m_oldY, point.x, point.y, false);

	Handle(AIS_InteractiveContext) context = pView->GetDocument()->GetContext();

	if (abs(point.x - m_oldX) > MinimumSize && abs(point.y - m_oldY) > MinimumSize)
	{
		context->Select(m_oldX, m_oldY, point.x, point.y, pView->GetView(), true);
	}
	else
	{
		context->Select(true);
	}	

	m_isStarted = false;
}

void SelectionOperator::OnMouseMove(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	Handle(AIS_InteractiveContext) context = pView->GetDocument()->GetContext();
	context->MoveTo(point.x, point.y, pView->GetView(), true);

	if (!m_isStarted)
		OperatorBase::OnMouseMove(pView, nFlags, point);
	else
	{
		DrawRectangle(pView, m_oldX, m_oldY, point.x, point.y, true);
	}
}

void SelectionOperator::DrawRectangle(COCCTSampleView * pView, int minX, int minY, int maxX, int maxY, bool toDraw)
{
	Handle(AIS_InteractiveContext) context = pView->GetDocument()->GetContext();

	if (!toDraw)
	{
		context->Remove(m_rubberBand, false);
		context->CurrentViewer()->RedrawImmediate();
		return;
	}

	CRect rect;
	pView->GetWindowRect(rect);
	m_rubberBand->SetLineType(Aspect_TOL_SOLID);
	m_rubberBand->SetRectangle(minX, rect.Height() - minY, maxX, rect.Height() - maxY);
	if (!context->IsDisplayed(m_rubberBand))
	{
		context->Display(m_rubberBand, false);
	}
	else
	{
		context->Redisplay(m_rubberBand, false);
	}

	context->CurrentViewer()->RedrawImmediate();
}