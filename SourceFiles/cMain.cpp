#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxMDIParentFrame)
EVT_MENU(10001, cMain::OnMenuReset)
EVT_MENU(10002, cMain::OnMenuExit)
wxEND_EVENT_TABLE()

cMain::cMain() : wxMDIParentFrame(nullptr, wxID_ANY, "Pathfinding Visualization with WxWidgets", wxPoint(600, 300), wxSize(600, 600))
{
	//Adds new menu bar
	m_MenuBar = new wxMenuBar();
	this->SetMenuBar(m_MenuBar);

	//Add Menu for file operations
	wxMenu *menuFile = new wxMenu();
	menuFile->Append(10001, "Reset");
	menuFile->Append(10002, "Exit");
	
	//Add Program Menu to Menu Bar
	m_MenuBar->Append(menuFile, "Program");

	//Add a toolbar
	m_ToolBar = this-> CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);

	const char * buttonNames[] = {"Reset", "Starting Point", "Ending Point", "Obstacle", "Run"};

	for(int i = 0; i < 5; i++)
	{
		wxButton *b = new wxButton (m_ToolBar, 10010 + i, buttonNames[i], wxDefaultPosition, wxSize(120, 40), 0);
		b->SetBackgroundColour(wxColour(255, 0, 255));
		b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnButtonClick), nullptr);
		m_ToolBar->AddControl(b);	
	}
	m_ToolBar->Realize();

}


cMain::~cMain()
{

}

void cMain::OnMenuReset(wxCommandEvent & evt)
{

}

void cMain::OnButtonClick(wxCommandEvent & evt)
{

}


void cMain::OnMenuExit(wxCommandEvent & evt)
{
	Close();
	evt.Skip();
}
