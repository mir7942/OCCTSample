﻿
// OCCTSampleDoc.cpp: COCCTSampleDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OCCTSample.h"
#endif

#include <BRepPrimAPI_MakeCylinder.hxx>
#include <AIS_Shape.hxx>

#include "StepReader.h"
#include "IgesReader.h"
#include "OCCTSampleDoc.h"

#include <propkey.h>

// OCCT에서 사용하기 위해서는 아래 부분을 주석처리 해야 함
/*
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
*/

// COCCTSampleDoc

IMPLEMENT_DYNCREATE(COCCTSampleDoc, CDocument)

BEGIN_MESSAGE_MAP(COCCTSampleDoc, CDocument)
	ON_COMMAND(ID_FILE_IMPORT, &COCCTSampleDoc::OnFileImport)
END_MESSAGE_MAP()


// COCCTSampleDoc 생성/소멸

COCCTSampleDoc::COCCTSampleDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

COCCTSampleDoc::~COCCTSampleDoc()
{
}

void COCCTSampleDoc::InitializeDocument()
{
	Handle(Graphic3d_GraphicDriver) graphicDriver = static_cast<COCCTSampleApp *>(AfxGetApp())->GetGraphicDriver();
	
	// Viewer를 생성하고, 광원을 기본으로 설정한다.
	m_viewer = new V3d_Viewer(graphicDriver);
	m_viewer->SetDefaultLights();
	m_viewer->SetLightOn();

	// AIS_InteractiveContext를 생성한다.
	m_context = new AIS_InteractiveContext(m_viewer);
}

BOOL COCCTSampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	InitializeDocument();

	TopoDS_Shape shape = BRepPrimAPI_MakeCylinder(50.0, 200.0);
	
	Handle(AIS_Shape) aisShape = new AIS_Shape(shape);
	aisShape->SetDisplayMode(AIS_Shaded);
	GetContext()->Display(aisShape, true);

	return TRUE;
}

BOOL COCCTSampleDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	InitializeDocument();

	return TRUE;
}

// COCCTSampleDoc serialization

void COCCTSampleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void COCCTSampleDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void COCCTSampleDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void COCCTSampleDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COCCTSampleDoc 진단

#ifdef _DEBUG
void COCCTSampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COCCTSampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COCCTSampleDoc 명령

void COCCTSampleDoc::OnFileImport()
{
	CString strFilter = _T("STEP 파일 (*.stp)|*.stp|IGES 파일 (*.igs, *.iges)|*.igs;*.iges||");

	CFileDialog dialog(TRUE, _T("*.stp"), 0, OFN_HIDEREADONLY, strFilter);

	if (IDOK == dialog.DoModal())
	{
		TopoDS_Shape shape;

		CString extension = dialog.GetFileExt();
		if (extension == _T("stp"))
		{			
			StepReader reader;
			reader.Read(dialog.GetPathName(), shape);
		}
		else if (extension == _T("igs") || extension == _T("iges"))
		{
			IgesReader reader;
			reader.Read(dialog.GetPathName(), shape);
		}

		if (!shape.IsNull())
		{
			Handle(AIS_Shape) aisShape = new AIS_Shape(shape);
			aisShape->SetDisplayMode(AIS_Shaded);
			GetContext()->Display(aisShape, true);
		}
	}
}
