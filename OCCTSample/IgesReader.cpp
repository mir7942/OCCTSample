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
		// BSpline�� �ִ� �״�� �д´�. �̸� �⺻��(1)���� �����ϸ� ��� �������� �ɰ��� �� �ִ�.
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
