// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".


#include <wx/wxprec.h>
#include <wx/xml/xml.h>
#include <wx/msw/helpchm.h>
#include <pqxx/pqxx>

#include <wx/config.h>
//#include <wx/msw/statline.h>

#include <wx/gbsizer.h>

#include "datalayer.h"
#include "MapView.h"

#include <wx/vector.h>
#include <wx/arrstr.h>

#include <iostream>

wxConfig *config;

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
class MyApp: public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit();
public:
	wxCHMHelpController *m_helpCtrl;
};
class MyFrame: public wxFrame
{

private:
	void OnExit(wxCommandEvent& event);
	void OnOpenProject(wxCommandEvent& event);	
	void OnAddLayer(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
protected:
	wxListBox* m_listBox1;
//	wxScrolledWindow* m_scrolledWindow1;
	MapView* m_mapview;
	wxMenuBar* m_menubar1;
	wxMenu* m_menu1;
	wxMenu* m_menu2;

public:

	MyFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Qgis2wx"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

	~MyFrame();

public:
	DataLayer *m_DataLayer; 
};

enum
{
//	ID_Hello = 1  //replace  with ID_Open
	ID_OPEN_PROJECT,
	ID_ADD_LAYER
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)

	EVT_MENU(wxID_EXIT,  MyFrame::OnExit)

	EVT_MENU(ID_OPEN_PROJECT,   MyFrame::OnOpenProject)
    EVT_MENU(ID_ADD_LAYER, MyFrame::OnAddLayer)
wxEND_EVENT_TABLE()

IMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
	m_helpCtrl = new wxCHMHelpController;
	MyFrame *frame = new MyFrame( NULL, wxID_ANY, "QGIS2Wx", wxPoint(50, 50), wxSize(450, 340) );
	frame->Show( true );
	return true;
}

int MyApp::OnExit()
{
	delete m_helpCtrl;
	return 0;
}

MyFrame::MyFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	m_DataLayer = new DataLayer;

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	m_listBox1 = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer1->Add( m_listBox1, 0, wxALL|wxEXPAND, 5 );

	/*
	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	bSizer1->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );
	*/
	m_mapview = new MapView(m_DataLayer, this);
	bSizer1->Add( m_mapview, 1, wxEXPAND | wxALL, 5);


	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu1, ID_OPEN_PROJECT, wxString( wxT("Open Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem1 );

	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menu1, wxID_EXIT, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem2 );

	m_menubar1->Append( m_menu1, wxT("File") ); 

	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu2, ID_ADD_LAYER, wxString( wxT("Add Layer") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem3 );

	m_menubar1->Append( m_menu2, wxT("View") ); 

	this->SetMenuBar( m_menubar1 );

	this->Centre( wxBOTH );
}

MyFrame::~MyFrame()
{

}

/*
void MyFrame::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	wxCoord x1 = 50, y1 = 60;
	wxCoord x2 = 190, y2 = 60;

	dc.DrawLine(x1, y1, x2, y2);
}
*/

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}


class Qgis2wxDbSourceSelectDlg : public wxDialog 
{
private:

	wxDECLARE_EVENT_TABLE();
protected:

	wxButton* m_button1;
	wxButton* m_button2;
	wxButton* m_button3;
	wxStaticText* m_staticText1;

	wxButton* m_button13;
	wxButton* m_button14;
	wxButton* m_button15;
	wxArrayString conStrArray;

public:

	wxListBox* m_listBox2;
	wxComboBox* m_comboBox1;

	Qgis2wxDbSourceSelectDlg( DataLayer* dataLayer, MapView* mMapV, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add PostGIS Table(s)"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 269,286 ), long style = wxDEFAULT_DIALOG_STYLE ); 
	void OnNewConnection(wxCommandEvent& event);
	void OnEditConnection(wxCommandEvent& event);
	
	void OnConnect(wxCommandEvent& event);
	~Qgis2wxDbSourceSelectDlg();
public:
	DataLayer* mm_DataLayer;
	wxWindow* m_parent;

	MapView* mm_MapView;
};

enum
{
	ID_CONNECT,
	ID_NEW_CONNECTION,
	ID_EDIT_CONNECTION

};

wxBEGIN_EVENT_TABLE(Qgis2wxDbSourceSelectDlg, wxDialog)

	EVT_BUTTON(ID_NEW_CONNECTION,   Qgis2wxDbSourceSelectDlg::OnNewConnection)
	EVT_BUTTON(ID_CONNECT,   Qgis2wxDbSourceSelectDlg::OnConnect)
	EVT_BUTTON(ID_EDIT_CONNECTION,   Qgis2wxDbSourceSelectDlg::OnEditConnection)
	
//	EVT_BUTTON(wxID_OK,Qgis2wxDbSourceSelectDlg::OnOK)

wxEND_EVENT_TABLE()

enum
{
	//	ID_Hello = 1  //replace  with ID_Open
	ID_M_USERSTATICTEXT,
	ID_M_TESTBUTTON
};

class Qgs2WxNewConnection : public wxDialog 
{
private:


public:
	wxTextCtrl* m_textCtrl18;
protected:
	wxStaticText* m_staticText15;

	wxStaticText* m_staticText16;
	wxTextCtrl* m_textCtrlHost; //host
	wxStaticText* m_staticText17;
	wxTextCtrl* m_textCtrlDataBaseName; //database
	wxStaticText* m_staticText7;
	wxTextCtrl* m_textCtrlUserName; //username
	wxStaticText* m_staticText8;
	wxTextCtrl* m_textCtrlPassWord; //password
	wxButton* m_button11;
	wxCheckBox* m_checkBox2;
	wxButton* m_buttonOK;
	wxButton* m_buttonCancel;
	wxButton* m_button41;


	// Virtual event handlers, overide them in your derived class

	virtual void OnOK( wxCommandEvent& event );	
	virtual void OnCancel( wxCommandEvent& event );

	void testConnection(wxCommandEvent& event);

public:
	void test();
	Qgs2WxNewConnection( DataLayer* dataLayer, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Create a New PostGis Connection"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 418,231 ), long style = wxDEFAULT_DIALOG_STYLE ); 
	~Qgs2WxNewConnection();

public:

	bool isValidCon;//是否为可用
	wxString  ConnInfoRight;//连接字符串


};

Qgs2WxNewConnection::Qgs2WxNewConnection( DataLayer* dataLayer, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{


	//Init
	isValidCon = false;
	ConnInfoRight = "";

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Connection Information") ), wxVERTICAL );

	wxGridBagSizer* gbSizer2;
	gbSizer2 = new wxGridBagSizer( 0, 0 );
	gbSizer2->SetFlexibleDirection( wxBOTH );
	gbSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	gbSizer2->Add( m_staticText15, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl18 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_textCtrl18, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_staticText16 = new wxStaticText( this, wxID_ANY, wxT("Host"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	gbSizer2->Add( m_staticText16, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlHost = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_textCtrlHost, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_staticText17 = new wxStaticText( this, wxID_ANY, wxT("Database"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	gbSizer2->Add( m_staticText17, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlDataBaseName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	gbSizer2->Add( m_textCtrlDataBaseName, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );

	wxGridBagSizer* gbSizer3;
	gbSizer3 = new wxGridBagSizer( 0, 0 );
	gbSizer3->SetFlexibleDirection( wxBOTH );
	gbSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Username"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gbSizer3->Add( m_staticText7, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlUserName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_textCtrlUserName, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Password"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	gbSizer3->Add( m_staticText8, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrlPassWord = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_textCtrlPassWord, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_button11 = new wxButton( this, wxID_ANY, wxT("Test Connection"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_button11, wxGBPosition( 0, 4 ), wxGBSpan( 2, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	gbSizer2->Add( gbSizer3, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );


	sbSizer7->Add( gbSizer2, 0, wxEXPAND, 5 );

	m_checkBox2 = new wxCheckBox( this, wxID_ANY, wxT("Save Password"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer7->Add( m_checkBox2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer12->Add( sbSizer7, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	m_buttonOK = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_buttonOK, 0, wxALL, 5 );

	m_buttonCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_buttonCancel, 0, wxALL, 5 );

	m_button41 = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_button41, 0, wxALL, 5 );

	bSizer12->Add( bSizer15, 1, 0, 5 );

	this->SetSizer( bSizer12 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Qgs2WxNewConnection::testConnection ), NULL, this );
//	m_buttonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Qgs2WxNewConnection::OnOK ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Qgs2WxNewConnection::OnCancel ), NULL, this );
}

Qgs2WxNewConnection::~Qgs2WxNewConnection()
{
	// Disconnect Events
//	m_button11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Qgs2WxNewConnection::testConnection ), NULL, this );
  //  m_buttonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Qgs2WxNewConnection::OnOK ), NULL, this );
    m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Qgs2WxNewConnection::OnCancel ), NULL, this );


}

void Qgs2WxNewConnection::OnOK(wxCommandEvent& event ){

	wxString connInfo = "host=" + m_textCtrlHost->GetValue() + " dbname=" + m_textCtrlDataBaseName->GetValue() + " user=" + m_textCtrlUserName->GetValue() + " password=" + m_textCtrlPassWord->GetValue()+" port=5432" ;
	try
	{
		pqxx::connection C(connInfo);
		std::string tableName("tabletwo");

		if (C.is_open()) {

			isValidCon = true;
			ConnInfoRight = connInfo;
			
			//std::cout << "We are connected to " << C.dbname() << endl;
			wxString successMsg = wxString::Format(wxT("We are connected to %s"), C.dbname() );	
			wxMessageBox( successMsg,
				_("Database Connection Status"),
				wxOK | wxICON_INFORMATION, this );
		} 
		else {

			wxString unsuccessMsg = wxString::Format(wxT("We are not connected to %s"), C.dbname() );
			wxMessageBox( unsuccessMsg,
				_("Database Connection Status"),
				wxOK | wxICON_INFORMATION, this );

		}

	}
	catch(const pqxx::failure &ec)
	{
		wxMessageBox( _("Connection failed!"),
			_("Database Connection Status"),
			wxOK | wxICON_INFORMATION, this );
	}

	

	if(isValidCon)
	{
				wxMessageBox( _("Connection String Succeed Add"),
				_("Connection Add Status"), 
				wxOK | wxICON_INFORMATION, this );
	}
	else
	{
		wxMessageBox( _("It is not a valid connection"),
			_("Connection Add Status"), 
			wxOK | wxICON_INFORMATION, this );
	}
	
}

void Qgs2WxNewConnection::OnCancel(wxCommandEvent& event ){

	isValidCon = false;
	ConnInfoRight = "";

	this->Close(true);

}

void Qgs2WxNewConnection::test(){
	
	wxString connInfo = "host=" + m_textCtrlHost->GetValue() + " dbname=" + m_textCtrlDataBaseName->GetValue() + " user=" + m_textCtrlUserName->GetValue() + " password=" + m_textCtrlPassWord->GetValue()+" port=5432" ;

	try
	{
		pqxx::connection C(connInfo);
		std::string tableName("tabletwo");

		if (C.is_open()) {

			isValidCon = true;
			ConnInfoRight = connInfo;

			//std::cout << "We are connected to " << C.dbname() << endl;
			wxString successMsg = wxString::Format(wxT("We are connected to %s"), C.dbname() );	
			wxMessageBox( successMsg,
				_("Database Connection Status"),
				wxOK | wxICON_INFORMATION, this );
		} 
		else {

			wxString unsuccessMsg = wxString::Format(wxT("We are not connected to %s"), C.dbname() );
			wxMessageBox( unsuccessMsg,
				_("Database Connection Status"),
				wxOK | wxICON_INFORMATION, this );

		}

	}
	catch(const pqxx::failure &ec)
	{
		wxMessageBox( _("Connection failed!"),
			_("Database Connection Status"),
			wxOK | wxICON_INFORMATION, this );
	}

}
void Qgs2WxNewConnection::testConnection(wxCommandEvent& event){

	test();
	/*
	// following line uses Qt SQL plugin - currently not used
	// QSqlDatabase *testCon = QSqlDatabase::addDatabase("QPSQL7","testconnection")

	*/
}

void Qgis2wxDbSourceSelectDlg::OnNewConnection(wxCommandEvent& event)
{
	Qgs2WxNewConnection dlg(this->mm_DataLayer, this);

	if ( dlg.ShowModal() == wxID_OK )
	{
		dlg.test();
		if(dlg.isValidCon == true)
		{

			m_comboBox1->Append( dlg.m_textCtrl18->GetValue() );
			
			config = new wxConfig("a");
			config->Write("a", dlg.ConnInfoRight);
			wxConfig::Set(config);

			conStrArray.Add( dlg.ConnInfoRight);
		}

	}
}

void Qgis2wxDbSourceSelectDlg::OnConnect(wxCommandEvent& event){

	wxString strItem = m_comboBox1->GetValue();

	if(strItem=="")
	{

	}
	else
	{
		wxConfig::Get(config);
		wxString conStr = config->Read(strItem);
		if(conStr!="")
		{
			//Table 表中显示内容

			//		PgDatabase *pd = new PgDatabase(conStr);
			pqxx::connection c(conStr);
			pqxx::work txn(c);


			//暂时强加上 railroads表
			m_listBox2->Append("railroads");

			//			wxString sql = "select f_geometry_column from geometry_columns where f_table_name='railroads'";
			pqxx::result r = txn.exec("select f_geometry_column from geometry_columns where f_table_name='railroads'");
			//	    pqxx::result r = txn.exec("select * from railroads");
			int count = r.size();
			if(r.size()!=1){

			}
			else
			{
				std::string tmp;
				std::string tablename;
				tablename = "railroads";
				for (pqxx::result::size_type i = 0; i != r.size(); ++i)
					tmp = r[0][0].as<std::string>();
				//int tmp = r.begin()[0].as<int>();

				std::string sql = "select ST_xmax(ST_extent(" + tmp + ")) as xmax,"
					"ST_xmin(ST_extent(" + tmp + ")) as xmin,"
					"ST_ymax(ST_extent(" + tmp + ")) as ymax,"
					"ST_ymin(ST_extent(" + tmp + ")) as ymin" + 
					" from " + tablename;

				r = txn.exec(sql);

				wxRect layerExtent;

				double xmax = r[0]["xmax"].as<double>();
				double xmin = r[0]["xmin"].as<double>();
				double ymax = r[0]["ymax"].as<double>();
				double ymin = r[0]["ymin"].as<double>();


				struct MyRect{

					double xmin;
					double xmax;
					double ymin;
					double ymax;

					MyRect()
					{
						xmin = 0;
						xmax = 0;
						ymin = 0;
						ymax = 0;
					}
				};

				MyRect m_rect;
				m_rect.xmin = xmin;
				m_rect.xmax = xmax;
				m_rect.ymin = ymin;
				m_rect.ymax = xmax;

				mm_DataLayer->m_rect->SetLeft(xmin);
				mm_DataLayer->m_rect->SetRight(xmax);
				mm_DataLayer->m_rect->SetTop(ymax);
				mm_DataLayer->m_rect->SetBottom(ymin);



				//执行查询
				sql = "select ""ST_AsText(" + tmp + ") from " + tablename;
				r = txn.exec(sql);

				count = r.size();

				
				//typedef std::vector<wxString> LineString;
				//std::vector<LineString> LineStringVector;

				wxVector<wxArrayString> LineStringVector;
				wxVector<wxString> PointVector;

				for (pqxx::result::size_type i = 0; i != r.size(); ++i)
				{

					//std::vector<wxString> ptVector;
					wxArrayString ptVector;

					tmp = r[i][0].as<std::string>(); //one by one

					//LINESTRING， MULTILINESTRING 
					int k = tmp.find("LINESTRING");
					int l;

					int m, n;

	
					if((m = tmp.find("MULTILINESTRING"))>=0) //multilinestring  sample MULTILINESTRING((0 0,1 1,1 2),(2 3,3 2,5 4),(7 8, 9 10, 11 12, 14 15))  
					{
						wxString strLines = tmp.substr(16, tmp.length()-17);  //(0 0,1 1,1 2),(2 3,3 2,5 4),(7 8, 9 10, 11 12, 14 15) or
						// (0 0,1 1,1 2)
						wxString strLeftLine;//last rest line
						strLeftLine = strLines; //initialize


						wxString strs = "),";
						while( ( m = strLines.find(strs) )>0 )// have multi linestring
						{
							wxString strLine = strLines.substr( 1, m ); // 0 0,1 1,1 2 or 0 0
							wxString strLeft;

							//strLine destruct to pt && store in the 
							{
								int p;
								strLeft = strLine; // avoid this situation 1 2
								while( ( p = strLine.find(',') )>0 )
								{
									wxString strPt = strLine.substr( 0, p );
									ptVector.push_back( strPt );

									strLeft = strLine.substr(p+1, strLine.length() - p); 
									strLine = strLeft;
								}
								ptVector.push_back( strLeft );
							}
							strLines = strLines.substr( m+2, strLines.Length() - m - 2 );

							//
							strLeftLine = strLines;
							//
						}
						// do the clean work
						//get off the ()

						strLeftLine = strLeftLine.substr(1,strLeftLine.Length()-2);

						wxString strLeft = strLeftLine;

						wxString strPoint;
						while( ( m = strLeft.find(',') )>0 )
						{
							wxString strPt = strLeft.substr( 0, m );

							ptVector.push_back( strPt );

							strLeft = strLeft.substr(m+1, strPoint.length() - m); 

						}

						ptVector.push_back( strLeft );
						LineStringVector.push_back( ptVector );
					}

					else if( (m = tmp.find("LINESTRING"))>=0)//
					{
						k = tmp.find("(");
						l = tmp.find(")");
						wxString strPoint = tmp.substr(k+1,l-k-1);
						wxString strLeft;

						while( ( m = strPoint.find(',') )>0 )
						{
							wxString strPt = strPoint.substr( 0, m );
							ptVector.push_back( strPt );
							strLeft = strPoint.substr(m+1, strPoint.length() - m); 
							strPoint = strLeft;
						}
						ptVector.push_back( strLeft );
						LineStringVector.push_back( ptVector );
					}

					else if(( m = tmp.find("MULTIPOINT"))>=0)//
					{

					}
					else if(( m = tmp.find("POINT"))>=0)//
					{
						k = tmp.find("(");
						l = tmp.find(")");
						wxString strPoint = tmp.substr(k+1,l-k-1);
	
						PointVector.push_back( strPoint );
					}

				} 

				if( LineStringVector.size() > 0)
				{
					mm_DataLayer->lineSVector = LineStringVector;
				}
				if( PointVector.size() > 0)
				{
					mm_DataLayer->pointsVector = PointVector;
				}


			}

			//		    pqxx::result::size_type row = r.column_number("road_name");

		}
	}
}

void Qgis2wxDbSourceSelectDlg::OnEditConnection(wxCommandEvent& event){

	wxString tmp = wxString::Format(wxT("%d"), mm_DataLayer->a);
	

	wxMessageBox(tmp, _T("abc"));
}

Qgis2wxDbSourceSelectDlg::Qgis2wxDbSourceSelectDlg( DataLayer* dataLayer, MapView* m_MapV, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	mm_DataLayer = new DataLayer;
	mm_DataLayer = dataLayer;

	m_parent = new wxWindow;
	m_parent = parent;
	
	mm_MapView = new MapView(mm_DataLayer, m_MapV);
//	mm_MapView = m_MapV;

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Connection Information") ), wxVERTICAL );

	m_comboBox1 = new wxComboBox( this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	sbSizer2->Add( m_comboBox1, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_button1 = new wxButton( this, ID_CONNECT, wxT("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_button1, 0, wxALL, 5 );

	m_button2 = new wxButton( this, ID_NEW_CONNECTION, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_button2, 0, wxALL, 5 );

	m_button3 = new wxButton( this, ID_EDIT_CONNECTION, wxT("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_button3, 0, wxALL, 5 );


	sbSizer2->Add( fgSizer1, 0, wxEXPAND, 5 );


	bSizer2->Add( sbSizer2, 0, wxEXPAND, 5 );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Tables"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALL, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_listBox2 = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer3->Add( m_listBox2, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_button13 = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button13, 0, wxALIGN_BOTTOM|wxALL, 5 );

	m_button14 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button14, 0, wxALIGN_BOTTOM|wxALL, 5 );

	m_button15 = new wxButton( this, wxID_ANY, wxT("help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button15, 0, wxALIGN_BOTTOM|wxALL|wxEXPAND, 5 );


	bSizer3->Add( bSizer4, 0, wxEXPAND, 5 );


	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer2 );
	this->Layout();

	this->Centre( wxBOTH );
}

void MyFrame::OnAddLayer(wxCommandEvent& event)
{
	Qgis2wxDbSourceSelectDlg dlg(this->m_DataLayer, this->m_mapview, this);


	if(config!=NULL)
	{
		wxConfig::Get(config);
		wxString strCon = config->Read("a");
	}

	if ( dlg.ShowModal() == wxID_OK )
	{
		wxLogMessage("just test");
	}
}

void MyFrame::OnOpenProject(wxCommandEvent& event)
{
};

Qgis2wxDbSourceSelectDlg::~Qgis2wxDbSourceSelectDlg()
{

};





