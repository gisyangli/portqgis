#include "MapView.h"

//
//
IMPLEMENT_CLASS(MapView, wxWindow)

	BEGIN_EVENT_TABLE(MapView, wxWindow)
	EVT_PAINT(MapView::OnPaint)
//	EVT_ERASE_BACKGROUND(wxGISMapView::OnEraseBackground)
//	EVT_SIZE(MapView::OnSize)
	EVT_MOUSEWHEEL(MapView::OnMouseWheel)

	EVT_LEFT_DOWN(MapView::OnLBtnDown)
	EVT_LEFT_UP(MapView::OnLBtnUp)
	EVT_MOTION(MapView::OnMotion)

//	EVT_TIMER( TIMER_ID, wxGISMapView::OnTimer )
//	EVT_KEY_DOWN(wxGISMapView::OnKeyDown)
//	EVT_KEY_UP(wxGISMapView::OnKeyDown)
//	EVT_MOUSE_CAPTURE_LOST(wxGISMapView::OnCaptureLost)
//	EVT_MXMAP_DRAWING_START(wxGISMapView::OnMapDrawing)
//	EVT_MXMAP_DRAWING_STOP(wxGISMapView::OnMapDrawing)
//	EVT_MXMAP_LAYER_CHANGED(wxGISMapView::OnLayerChanged)
	END_EVENT_TABLE()


void MapView::OnMouseWheel(wxMouseEvent& event)
{

	int nDirection = event.GetWheelRotation();
	int nDelta = event.GetWheelDelta();
	int nFactor = nDirection / nDelta;

	double m_nFactor = 1;
	m_nFactor += (double)nFactor;

	double dZoom = 1;
	if(m_nFactor < 0)
		dZoom = fabs(1.0 / (m_nFactor - 1));
	else if(m_nFactor > 0)
		dZoom = 1 + m_nFactor;

}

void MapView::OnLBtnDown(wxMouseEvent& event)
{

}

void MapView::OnLBtnUp(wxMouseEvent& event)
{

}

void MapView::OnMotion(wxMouseEvent& event)
{

}

MapView::MapView(DataLayer* ly, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
	m_ly = ly;
	Create(parent, id, pos, size, style);
}

bool MapView::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
	if(!wxWindow::Create(parent, id, pos, size, style, name ))
		return false;
}

MapView::~MapView(void)
{
}

void MapView::DrawLine()
{
	wxClientDC dc(this);
	// draw some text
	dc.DrawText(wxT("Testing"), 40, 60); 
	// draw a circle
	dc.SetBrush(*wxGREEN_BRUSH); // green filling
	dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red outline
	dc.DrawCircle( wxPoint(200,100), 25 /* radius */ );

	// draw a rectangle
	dc.SetBrush(*wxBLUE_BRUSH); // blue filling
	dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
	dc.DrawRectangle( 300, 100, 400, 200 );
	// draw a line
	dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
	dc.DrawLine( 300, 100, 700, 300 ); // draw line across the rectangle
}

void MapView::OnPaint(wxPaintEvent & event)
{
	wxPaintDC dc(this);
	wxRect mm_Rect = this->GetRect(); //»ñÈ¡»æÍ¼ÇøÓò·¶Î§

	// 
	wxRect m_Rect(mm_Rect);

	double zoom = 2;
	if( 0 )
	{

		m_Rect.x = mm_Rect.x - mm_Rect.GetWidth() * (zoom -1)/2.0;
		m_Rect.y = mm_Rect.y - mm_Rect.GetHeight() * (zoom - 1)/2.0;
		m_Rect.SetWidth( mm_Rect.GetWidth()*zoom );
		m_Rect.SetHeight( mm_Rect.GetHeight()*zoom );
	
	}


	//transfer to real coor to client coor;
	//draw line
	//draw point3
	//draw polygon

	wxCoord xx1 , yy1 ;
	wxCoord xx2 , yy2;
	//dc.DrawLine( xx1, yy1, xx2, yy2 );

    //Line
	if( m_ly->lineSVector.size()>0 )
	{
		wxString tmp = wxString::Format(_T("%d"), m_ly->lineSVector.size());
		for( int i =0 ; i < m_ly->lineSVector.size(); i++)
		{
			wxArrayString strArrTmp = m_ly->lineSVector.at(i);

			int nSize = strArrTmp.size();
			wxPoint *pts = new wxPoint[strArrTmp.size()];

			wxPoint p1;
			wxPoint p2;

			for( int j = 0; j < strArrTmp.size(); j++ )
			{
				wxString strPt = strArrTmp.Item(j);
				int p = strPt.Find(" ");

				wxString strX = strPt.substr(0,p);
				wxString strY = strPt.substr(p+1,strPt.Length()-p);
				
				double a = atof(strX);
				double b = atof(strY);

				a = a - m_ly->m_rect->GetLeft();
				b = b - m_ly->m_rect->GetBottom();

				a = m_Rect.GetLeft() + ((double)m_Rect.GetWidth() / (double)m_ly->m_rect->GetWidth()) * (double)a;
				b = m_Rect.GetBottom() + ((double)m_Rect.GetHeight() / (double)m_ly->m_rect->GetHeight())* (double)b;

				(pts + j)->x = a;
				(pts + j)->y = b;
				if(j==0)
				{
					xx1 = a;
					yy1 = b;
				}
				else if(j==1)
				{
					xx2 = a;
					yy2 = b;
				}		
			}
			dc.DrawLines(nSize, pts);
		} 

	}
	//POINT
	if(m_ly->pointsVector.size()>0)
	{
		for(int i=0 ; i < m_ly->pointsVector.size(); i++ )
		{
			wxString strPt = m_ly->pointsVector.at(i);
			int p = strPt.Find(" ");

			wxString strX = strPt.substr(0,p);
			wxString strY = strPt.substr(p+1,strPt.Length()-p);
				
			double a = atof(strX);
			double b = atof(strY);

			a = a - m_ly->m_rect->GetLeft();
			b = b - m_ly->m_rect->GetBottom();

			a = m_Rect.GetLeft() + ((double)m_Rect.GetWidth() / (double)m_ly->m_rect->GetWidth()) * (double)a;
			b = m_Rect.GetBottom() + ((double)m_Rect.GetHeight() / (double)m_ly->m_rect->GetHeight())* (double)b;

			wxPoint pt;
			pt.x = a;
			pt.y = b;

			dc.DrawPoint( pt );
		}
	}

}