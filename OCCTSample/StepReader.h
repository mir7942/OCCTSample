#pragma once

#include <TopoDS_Shape.hxx>

class StepReader
{
public:
	StepReader();
	~StepReader();

	bool Read(const CString & fileName, TopoDS_Shape & shape);
};

