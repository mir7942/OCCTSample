#include "stdafx.h"
#include <V3d_View.hxx>
#include <AIS_InteractiveContext.hxx>
#include "OCCTSampleDoc.h"
#include "OCCTSampleView.h"
#include "ZoomWindowOperator.h"


ZoomWindowOperator::ZoomWindowOperator()
	: m_isStarted(false)
{
	m_rubberBand = new AIS_RubberBand();
}


ZoomWindowOperator::~ZoomWindowOperator()
{
}

void ZoomWindowOperator::OnLButtonDown(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	m_isStarted = true;
	m_oldX = point.x;
	m_oldY = point.y;
}

void ZoomWindowOperator::OnLButtonUp(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	const int ValZWMin = 1;

	DrawRectangle(pView, m_oldX, m_oldY, point.x, point.y, false);
	pView->GetView()->WindowFitAll(m_oldX, m_oldY, point.x, point.y);

	m_isStarted = false;
}

void ZoomWindowOperator::OnMouseMove(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	if (!m_isStarted)
		OperatorBase::OnMouseMove(pView, nFlags, point);
	else
	{
		DrawRectangle(pView, m_oldX, m_oldY, point.x, point.y, true);
	}
}

void ZoomWindowOperator::DrawRectangle(COCCTSampleView * pView, int minX, int minY, int maxX, int maxY, bool toDraw)
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