
// OCCTSampleView.h: COCCTSampleView 클래스의 인터페이스
//

#pragma once

#include <V3d_View.hxx>

class COCCTSampleDoc;
class OperatorBase;

class COCCTSampleView : public CView
{
protected: // serialization에서만 만들어집니다.
	COCCTSampleView() noexcept;
	DECLARE_DYNCREATE(COCCTSampleView)

// 특성입니다.
private:
	Handle(V3d_View) m_view;
	int m_width;
	int m_height;

	OperatorBase * m_pOperator;

public:
	COCCTSampleDoc* GetDocument() const;
	Handle(V3d_View) GetView() const { return m_view; }

	void SetOperator(OperatorBase * pOperator);
	OperatorBase * GetOperator() const { return m_pOperator; }

// 작업입니다.
public:
	void FitAll();

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	virtual void OnInitialUpdate();

// 구현입니다.
public:
	virtual ~COCCTSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()	
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);	
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);	
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	afx_msg void OnViewRotate();
	afx_msg void OnViewPan();
	afx_msg void OnViewZoom();
	afx_msg void OnViewZoomWindow();
	afx_msg void OnSelect();
};

#ifndef _DEBUG  // OCCTSampleView.cpp의 디버그 버전
inline COCCTSampleDoc* COCCTSampleView::GetDocument() const
   { return reinterpret_cast<COCCTSampleDoc*>(m_pDocument); }
#endif

