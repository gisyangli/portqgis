#ifndef DATALAYER_H
#define DATALAYER_H


#include <wx/vector.h>
#include <wx/arrstr.h>

//#include <iostream>
/*
	typedef std::vector<wxString> LineString;
	std::vector<LineString> LineStringVector;
	*/

class DataLayer
{



public:
	DataLayer(void);
    //DataLayer(DataLayer* const p);
	~DataLayer();
public:
	int a;

	
	//LineString* lineS;
	//LineStringVector* lineSVector;
	
	// Line
	wxArrayString lineS;
    wxVector<wxArrayString> lineSVector;
	
	//Point
	wxVector<wxString> pointsVector;



	wxRect* m_rect;

};

#endif