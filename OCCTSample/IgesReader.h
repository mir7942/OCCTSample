#pragma once

#include <TopoDS_Shape.hxx>

class IgesReader
{
public:
	IgesReader();
	~IgesReader();

	bool Read(const CString & fileName, TopoDS_Shape & shape);
};

