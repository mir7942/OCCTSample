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
		// 마우스로 선택한 영역이 크면 영역 선택을 한다.
		context->Select(m_oldX, m_oldY, point.x, point.y, pView->GetView(), true);
	}
	else
	{
		// 마우스로 선택한 영역이 작으면 현재 위치를 선택한다.
		context->Select(true);
	}	

	m_isStarted = false;
}

void SelectionOperator::OnMouseMove(COCCTSampleView * pView, UINT nFlags, CPoint point)
{
	Handle(AIS_InteractiveContext) context = pView->GetDocument()->GetContext();
	// 이동한 마우스 위치를 반영한다.
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