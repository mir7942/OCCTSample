#include "stdafx.h"
#include <STEPControl_Reader.hxx>
#include "StepReader.h"


StepReader::StepReader()
{
}


StepReader::~StepReader()
{
}

bool StepReader::Read(const CString & fileName, TopoDS_Shape & shape)
{
	// CString에서 OCCT가 읽을 수 있는 문자열로 변환한다.
	::TCollection_AsciiString ansiStr(fileName);

	STEPControl_Reader reader;
	// 파일을 읽는다.
	IFSelect_ReturnStatus status = reader.ReadFile(ansiStr.ToCString());
	if (status == IFSelect_RetDone)
	{
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
