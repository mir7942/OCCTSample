#include "stdafx.h"
#include <IGESControl_Reader.hxx>
#include <Interface_Static.hxx>
#include "IgesReader.h"


IgesReader::IgesReader()
{
}


IgesReader::~IgesReader()
{
}

bool IgesReader::Read(const CString & fileName, TopoDS_Shape & shape)
{
	// CString에서 OCCT가 읽을 수 있는 문자열로 변환한다.
	::TCollection_AsciiString ansiStr(fileName);

	IGESControl_Reader reader;
	// 파일을 읽는다.
	IFSelect_ReturnStatus status = reader.ReadFile(ansiStr.ToCString());
	if (status == IFSelect_RetDone)
	{
		// BSpline을 있는 그대로 읽는다. 이를 기본값(1)으로 설정하면 곡선이 직선으로 쪼개질 수 있다.
		Interface_Static::SetIVal("read.iges.bspline.continuity", 0);
		// 읽은 내용을 변환한다.
		reader.TransferRoots();

		if (reader.NbShapes() > 0)
		{
			// 읽은 형상이 한 개 이상이면 한 개의 형상으로 합쳐 가져온다.
			shape = reader.OneShape();
			return true;
		}
	}

	return false;
}
