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
	::TCollection_AsciiString ansiStr(fileName);

	IGESControl_Reader reader;
	IFSelect_ReturnStatus status = reader.ReadFile(ansiStr.ToCString());
	if (status == IFSelect_RetDone)
	{
		// BSpline을 있는 그대로 읽는다. 이를 기본값(1)으로 설정하면 곡선이 직선으로 쪼개질 수 있다.
		Interface_Static::SetIVal("read.iges.bspline.continuity", 0);

		reader.TransferRoots();

		if (reader.NbShapes() > 0)
		{
			shape = reader.OneShape();
			return true;
		}
	}

	return false;
}
