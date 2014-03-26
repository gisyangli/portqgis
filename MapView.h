
#ifndef MAPVIEW_H
#define MAPVIEW_H


#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>

#include <wx/settings.h>
#include <wx/dcclient.h>
#include <wx/msgdlg.h>

#include "datalayer.h"

class WXEXPORT MapView: 
	public wxWindow
{
	DECLARE_CLASS(MapView)
public:
	MapView(void);
	MapView(DataLayer* ly, wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxCLIP_CHILDREN | wxNO_FULL_REPAINT_ON_RESIZE);//wxSTATIC_BORDER|
	virtual ~MapView(void);
	void OnPaint(wxPaintEvent & event);
	virtual bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxCLIP_CHILDREN | wxNO_FULL_REPAINT_ON_RESIZE, const wxString& name = wxT("GISMapView"));//wxSTATIC_BORDER|

	void OnMouseWheel(wxMouseEvent& event);
	void OnLBtnDown(wxMouseEvent& event);
	void OnLBtnUp(wxMouseEvent& event);
	void OnMotion(wxMouseEvent& event);

	void DrawLine();
private:
	DECLARE_EVENT_TABLE()
public:
	DataLayer* m_ly;

};

#endif