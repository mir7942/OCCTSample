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
	::TCollection_AsciiString ansiStr(fileName);

	STEPControl_Reader reader;
	IFSelect_ReturnStatus status = reader.ReadFile(ansiStr.ToCString());
	if (status == IFSelect_RetDone)
	{
		reader.TransferRoots();

		if (reader.NbShapes() > 0)
		{
			shape = reader.OneShape();
			return true;
		}
	}

	return false;
}
