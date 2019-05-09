
// OCCTSampleView.cpp: COCCTSampleView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OCCTSample.h"
#endif

#include <OpenGl_GraphicDriver.hxx>
#include <WNT_Window.hxx>

#include "OperatorBase.h"
#include "RotationOperator.h"
#include "PanOperator.h"
#include "ZoomOperator.h"
#include "ZoomWindowOperator.h"
#include "SelectionOperator.h"
#include "OCCTSampleDoc.h"
#include "OCCTSampleView.h"

// OCCT에서 사용하기 위해서는 아래 부분을 주석처리 해야 함
/*
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
*/

// COCCTSampleView

IMPLEMENT_DYNCREATE(COCCTSampleView, CView)

BEGIN_MESSAGE_MAP(COCCTSampleView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COCCTSampleView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()	
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()	
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_VIEW_ROTATE, &COCCTSampleView::OnViewRotate)
	ON_COMMAND(ID_VIEW_PAN, &COCCTSampleView::OnViewPan)
	ON_COMMAND(ID_VIEW_ZOOM, &COCCTSampleView::OnViewZoom)
	ON_COMMAND(ID_VIEW_ZOOM_WINDOW, &COCCTSampleView::OnViewZoomWindow)
	ON_COMMAND(ID_VIEW_ZOOM_ALL, &COCCTSampleView::OnViewZoomAll)
	ON_COMMAND(ID_SELECT, &COCCTSampleView::OnSelect)
	ON_COMMAND(ID_VIEW_DEFAULT, &COCCTSampleView::OnViewDefault)
	ON_COMMAND(ID_VIEW_FRONT, &COCCTSampleView::OnViewFront)
	ON_COMMAND(ID_VIEW_BACK, &COCCTSampleView::OnViewBack)
	ON_COMMAND(ID_VIEW_LEFT, &COCCTSampleView::OnViewLeft)
	ON_COMMAND(ID_VIEW_RIGHT, &COCCTSampleView::OnViewRight)
	ON_COMMAND(ID_VIEW_TOP, &COCCTSampleView::OnViewTop)
	ON_COMMAND(ID_VIEW_BOTTOM, &COCCTSampleView::OnViewBottom)
END_MESSAGE_MAP()

// COCCTSampleView 생성/소멸

COCCTSampleView::COCCTSampleView() noexcept
	: m_pOperator(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

COCCTSampleView::~COCCTSampleView()
{
	if (m_pOperator != nullptr)
		delete m_pOperator;
	m_pOperator = nullptr;

	m_view->Remove();
}

BOOL COCCTSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.lpszClass = ::AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC, ::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return CView::PreCreateWindow(cs);
}

// COCCTSampleView 그리기

void COCCTSampleView::OnDraw(CDC* /*pDC*/)
{
	COCCTSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
			
	m_view->Redraw();
}


// COCCTSampleView 인쇄


void COCCTSampleView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COCCTSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COCCTSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COCCTSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void COCCTSampleView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COCCTSampleView 진단

#ifdef _DEBUG
void COCCTSampleView::AssertValid() const
{
	CView::AssertValid();
}

void COCCTSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COCCTSampleDoc* COCCTSampleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COCCTSampleDoc)));
	return (COCCTSampleDoc*)m_pDocument;
}
#endif //_DEBUG


// COCCTSampleView 메시지 처리기


void COCCTSampleView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// View를 생성한다.
	m_view = GetDocument()->GetViewer()->CreateView();

	// 윈도우를 생성한다.
	Handle(WNT_Window) window = new WNT_Window(GetSafeHwnd());
	// View와 Window를 연결한다.
	m_view->SetWindow(window);

	if (!window->IsMapped())
	{
		window->Map();
	}

	// 좌표계를 표시한다.
	m_view->ZBufferTriedronSetup();
	m_view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_BLACK, 0.07, V3d_ZBUFFER);

	SetOperator(new RotationOperator());
}

void COCCTSampleView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (!m_view.IsNull())
		m_view->MustBeResized();
}

void COCCTSampleView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	GetOperator()->OnLButtonDblClk(this, nFlags, point);
}

void COCCTSampleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	GetOperator()->OnLButtonDown(this, nFlags, point);
}

void COCCTSampleView::OnLButtonUp(UINT nFlags, CPoint point)
{
	GetOperator()->OnLButtonUp(this, nFlags, point);
}

void COCCTSampleView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	GetOperator()->OnMButtonDblClk(this, nFlags, point);
}


void COCCTSampleView::OnMButtonDown(UINT nFlags, CPoint point)
{
	GetOperator()->OnMButtonDown(this, nFlags, point);
}


void COCCTSampleView::OnMButtonUp(UINT nFlags, CPoint point)
{
	GetOperator()->OnMButtonUp(this, nFlags, point);
}

void COCCTSampleView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	GetOperator()->OnRButtonDblClk(this, nFlags, point);
}

void COCCTSampleView::OnRButtonDown(UINT nFlags, CPoint point)
{
	GetOperator()->OnRButtonDown(this, nFlags, point);
}

void COCCTSampleView::OnRButtonUp(UINT nFlags, CPoint point)
{
	GetOperator()->OnRButtonUp(this, nFlags, point);
}

BOOL COCCTSampleView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	return GetOperator()->OnMouseWheel(this, nFlags, zDelta, pt);
}

void COCCTSampleView::OnMouseMove(UINT nFlags, CPoint point)
{
	GetOperator()->OnMouseMove(this, nFlags, point);
}

void COCCTSampleView::SetOperator(OperatorBase * pOperator)
{
	if (m_pOperator != nullptr)
		delete m_pOperator;

	m_pOperator = pOperator;
}

void COCCTSampleView::OnViewRotate()
{
	SetOperator(new RotationOperator());
}

void COCCTSampleView::OnViewPan()
{
	SetOperator(new PanOperator());
}

void COCCTSampleView::OnViewZoom()
{
	SetOperator(new ZoomOperator());
}

void COCCTSampleView::OnViewZoomWindow()
{
	SetOperator(new ZoomWindowOperator());
}

void COCCTSampleView::OnViewZoomAll()
{
	m_view->FitAll();
	m_view->ZFitAll();	
}

void COCCTSampleView::OnSelect()
{
	SetOperator(new SelectionOperator());
}

void COCCTSampleView::OnViewDefault()
{
	m_view->Reset();
	m_view->FitAll();
	m_view->ZFitAll();
}

void COCCTSampleView::OnViewFront()
{
	m_view->SetProj(V3d_Xpos);
}

void COCCTSampleView::OnViewBack()
{
	m_view->SetProj(V3d_Xneg);
}

void COCCTSampleView::OnViewLeft()
{
	m_view->SetProj(V3d_Yneg);
}

void COCCTSampleView::OnViewRight()
{
	m_view->SetProj(V3d_Ypos);
}

void COCCTSampleView::OnViewTop()
{
	m_view->SetProj(V3d_Zpos);
}

void COCCTSampleView::OnViewBottom()
{
	m_view->SetProj(V3d_Zneg);
}