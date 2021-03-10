#include "cMain.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

#define pixelOffset 5 * m_gridDim 
#define blockOffset 5

wxBEGIN_EVENT_TABLE(cMain, wxMDIParentFrame)
EVT_MENU(10001, cMain::OnMenuReset)
EVT_MENU(10002, cMain::OnMenuExit)
EVT_PAINT(cMain::OnPaint)
EVT_LEFT_DOWN(cMain::OnMouseClick)
wxEND_EVENT_TABLE()

int cMain::m_colour = 0;
int cMain::m_arrayOfColours[20][20] = {0};
Pair cMain::m_src = make_pair(0, 0);
Pair cMain::m_dst = make_pair(19, 19);

cMain::cMain() : wxMDIParentFrame(nullptr, wxID_ANY, "Pathfinding Visualization with WxWidgets", wxPoint(600, 300), wxSize(610, 710))
{
	wxPanel* p = new wxPanel(this);
  	//p->SetBackgroundColour(*wxRED);
	
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	p->Connect( wxID_ANY,
        wxEVT_LEFT_DOWN,
        wxMouseEventHandler(cMain::OnMouseClick), NULL, this);

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
	for(int i = 0; i < m_gridDim; i++)
	{
		for(int j = 0; j < m_gridDim; j++)
		{
			std::cout << cMain::GetArray(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

void cMain::OnButtonClick(wxCommandEvent & evt)
{
	int foo = evt.GetId() - 10010;
	
	if(foo == 1)
	{
		int three = 3;
		cMain::SetColour(three);
	}

	if(foo == 2)
	{
		cMain::SetColour(foo);

	}
	
	if(foo == 3)
	{
		int one = 1;
		cMain::SetColour(one);
	}

	if(foo == 4)
	{
		Pair src = cMain::m_src;
		Pair dest = cMain::m_dst;
		aStarSearch(cMain::m_arrayOfColours, src, dest);
	}
}


void cMain::OnMenuExit(wxCommandEvent & evt)
{
	Close();
	evt.Skip();
}

void cMain::OnMouseClick(wxMouseEvent & evt)
{
	int xCoord = evt.GetX() / m_pixelSize - blockOffset;
	int yCoord = evt.GetY() / m_pixelSize - blockOffset;
	std::cout << "X: " << xCoord << " Y: " << yCoord << " ID: " << cMain::GetColour() << std::endl;
	if(xCoord >= 0 && xCoord < m_gridDim && yCoord >= 0 && yCoord < m_gridDim)
	{
		cMain::SetArray(xCoord, yCoord, cMain::GetColour());
		if(cMain::GetColour() == 3)
			cMain::SetSrc(xCoord, yCoord);

		if(cMain::GetColour() == 2)
			cMain::SetDst(xCoord, yCoord);
	}
	this->Refresh(false);
}

void cMain::OnDraw(wxDC & dc)
{
	dc.Clear();	

	wxBrush brush = dc.GetBrush();
	wxPen pen = dc.GetPen();

	pen.SetStyle(wxPENSTYLE_SOLID);
	pen.SetColour(wxColour(255, 255, 255));

	dc.SetPen(pen);

	for(int i = 0; i < m_gridDim; i++)
		for(int j = 0; j < m_gridDim; j++)
		{
			//std::cout << cMain::GetArray(i, j);
			
			//Obstacle
			if(cMain::GetArray(i, j) == 1)
			{
				brush.SetColour(wxColour(0, 0, 0));
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}
			//Ending Point
			else if(cMain::GetArray(i, j) == 2)
			{
				brush.SetColour(wxColour(255, 0, 0));
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}
			//Starting Point
			else if(cMain::GetArray(i, j) == 3)
			{
				brush.SetColour(wxColour(0, 255, 0));
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}
			else
			{
				brush.SetColour(wxColour(255, 229, 124));
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}


			dc.SetBrush(brush);
			dc.DrawRectangle(i * m_gridDim + pixelOffset, j * m_gridDim + pixelOffset, m_pixelSize, m_pixelSize);
		}

}

void cMain::OnPaint(wxPaintEvent & evt)
{
	wxBufferedPaintDC dc(this);

	this->PrepareDC(dc);
	this->OnDraw(dc);
}

//Setters and Getters
void cMain::SetSrc(int i, int j)
{
	cMain::m_src = make_pair(i, j);
}

void cMain::SetDst(int i, int j)
{
	cMain::m_dst = make_pair(i, j);
}

void cMain::SetColour(int & c)
{
	cMain::m_colour = c;
}

void cMain::SetArray(int row, int col, int c)
{
	cMain::m_arrayOfColours[row][col] = c;
}

int cMain::GetArray(int r, int c)
{
	return cMain::m_arrayOfColours[r][c];
}

int cMain::GetColour()
{
	return cMain::m_colour;
}

Pair cMain::GetSrc()
{
	return m_src;
}

Pair cMain::GetDst()
{
	return m_dst;
}
