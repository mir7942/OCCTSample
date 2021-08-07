
// OCCTSampleDoc.h: COCCTSampleDoc 클래스의 인터페이스
//


#pragma once

#include <V3d_Viewer.hxx>
#include <AIS_InteractiveContext.hxx>

class COCCTSampleDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	COCCTSampleDoc() noexcept;
	DECLARE_DYNCREATE(COCCTSampleDoc)

// 특성입니다.
private:
	Handle(V3d_Viewer) m_viewer;
	Handle(AIS_InteractiveContext) m_context;

public:
	Handle(AIS_InteractiveContext) GetContext() const { return m_context; }
	Handle(V3d_Viewer) GetViewer() const { return m_viewer; }

// 작업입니다.
private:
	void InitializeDocument();
	int GetFileCount(const CString& path) const;
	std::vector<Handle(AIS_InteractiveObject)> GetSelectedObjects() const;

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS
	
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

// 구현입니다.
public:
	virtual ~COCCTSampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	
public:
	afx_msg void OnFileImport();
	afx_msg void OnFileImportFolder();
	afx_msg void OnEditClear();
	afx_msg void OnEditClearAll();
	afx_msg void OnBooleanUnion();
};
