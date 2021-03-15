#include "cMain.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"
#include <bits/stdc++.h>
#include <thread>
#include <chrono>

#define pixelOffset 5 * cMain::GetGridDim() 
#define blockOffset 5

#define DELAY 5

wxBEGIN_EVENT_TABLE(cMain, wxMDIParentFrame)
EVT_MENU(10001, cMain::OnMenuReset)
EVT_MENU(10002, cMain::OnMenuExit)
EVT_BUTTON(wxID_ANY, cMain::OnButtonClick)
EVT_PAINT(cMain::OnPaint)
EVT_LEFT_DOWN(cMain::OnMouseClick)

wxEND_EVENT_TABLE()

int cMain::m_colour = 0;
int cMain::m_arrayOfColours[20][20] = {0};
Pair cMain::m_src = std::make_pair(0, 0);
Pair cMain::m_dst = std::make_pair(19, 19);

cMain::cMain() : wxMDIParentFrame(nullptr, wxID_ANY, "Pathfinding Visualization with WxWidgets", wxPoint(600, 300), wxSize(610, 710))
{
	cMain::m_arrayOfColours[0][0] = 3;
	cMain::m_arrayOfColours[19][19] = 2;
	
	wxPanel* p = new wxPanel(this);
  	//p->SetBackgroundColour(*wxRED);
	
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	p->Connect( wxID_ANY, wxEVT_LEFT_DOWN, wxMouseEventHandler(cMain::OnMouseClick), NULL, this);

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
		//b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnButtonClick), nullptr);
		m_ToolBar->AddControl(b);	
	}
	m_ToolBar->Realize();

}


cMain::~cMain()
{
	
}

void cMain::OnMenuReset(wxCommandEvent & evt)
{
	for(int i = 0; i < cMain::GetGridDim(); i++)
	{
		for(int j = 0; j < cMain::GetGridDim(); j++)
		{
			cMain::SetArray(i, j, 0); 
		}
	}
	cMain::SetSrc(0, 0);
	cMain::SetDst(19, 19);
	cMain::SetArray(0, 0, 3);
	cMain::SetArray(19, 19, 2);

	this->Refresh(false);
}

void cMain::OnButtonClick(wxCommandEvent & evt)
{
	int foo = evt.GetId() - 10010;

	if(foo == 0)
	{
	
		for(int i = 0; i < cMain::GetGridDim(); i++)
			for(int j = 0; j < cMain::GetGridDim(); j++)
			{
				cMain::SetArray(i, j, 0); 
			}
		cMain::SetSrc(0, 0);	
		cMain::SetDst(19, 19);
		cMain::SetArray(0, 0, 3);
		cMain::SetArray(19, 19, 2);
	}


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
		aStarSearch(cMain::GetWholeArray(), cMain::GetSrc(), cMain::GetDst());
	}
	this->Refresh(false);
}


void cMain::OnMenuExit(wxCommandEvent & evt)
{
	Close();
	evt.Skip();
}

void cMain::OnMouseClick(wxMouseEvent & evt)
{
	int xCoord = evt.GetX() / cMain::GetPixelSize() - blockOffset;
	int yCoord = evt.GetY() / cMain::GetPixelSize() - blockOffset;
	//std::cout << "X: " << xCoord << " Y: " << yCoord << " ID: " << cMain::GetColour() << std::endl;
	if(xCoord >= 0 && xCoord < cMain::GetGridDim() && yCoord >= 0 && yCoord < cMain::GetGridDim())
	{
		cMain::SetArray(xCoord, yCoord, cMain::GetColour());
		if(cMain::GetColour() == 3)
		{
			cMain::SetArray(cMain::GetSrcFirst(), cMain::GetSrcSecond(), 0);
			cMain::SetSrc(xCoord, yCoord);
		}
		
		if(cMain::GetColour() == 2)
		{
			cMain::SetArray(cMain::GetDstFirst(), cMain::GetDstSecond(), 0);	
			cMain::SetDst(xCoord, yCoord);
		}
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

	for(int i = 0; i < cMain::GetGridDim(); i++)
		for(int j = 0; j < cMain::GetGridDim(); j++)
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
				brush.SetColour(wxColour(0, 0, 255));
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}
			else if(cMain::GetArray(i, j) == 10)
			{
				
				brush.SetColour(wxColour(0, 255, 0));
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}
			else if(cMain::GetArray(i, j) == 11)
			{
				brush.SetColour(wxColour(208, 240, 192));
                                brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}
			else
			{
				brush.SetColour(wxColour(255, 229, 124));
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}

			dc.SetBrush(brush);
			dc.DrawRectangle(i * cMain::GetGridDim() + pixelOffset, j * cMain::GetGridDim() + pixelOffset, cMain::GetPixelSize(), cMain::GetPixelSize());
		}

}

void cMain::OnPaint(wxPaintEvent & evt)
{
	wxBufferedPaintDC dc(this);
	
	this->PrepareDC(dc);
	this->OnDraw(dc);
}

//Setters and Getters
int cMain::GetSrcFirst()
{
	return m_src.first;
}

int cMain::GetDstFirst()
{
	return m_dst.first;
}

int cMain::GetSrcSecond()
{
	return m_src.second;
}

int cMain::GetDstSecond()
{
	return m_dst.second;
}

void cMain::SetSrc(int i, int j)
{
	cMain::m_src = std::make_pair(i, j);
}

void cMain::SetDst(int i, int j)
{
	cMain::m_dst = std::make_pair(i, j);
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

int (*cMain::GetWholeArray())[20]
{
	return m_arrayOfColours;
}

const int cMain::GetGridDim()
{
	return m_gridDim;
}

const int cMain::GetPixelSize()
{
	return m_pixelSize;
}

////////////////A* algorithm/////////////////


// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool cMain::isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < Dim) && (col >= 0)
           && (col < Dim);
}
 
// A Utility Function to check whether the given cell is
// blocked or not
bool cMain::isUnBlocked(int grid[][Dim], int row, int col)
{
    // Returns true if the cell is not blocked else false
    if (grid[row][col]== 1) //<------------------------------------------CHANGED HERE
        return (false);
    else
        return (true);
}
 
// A Utility Function to check whether destination cell has
// been reached or not
bool cMain::isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}
 
// A Utility Function to calculate the 'h' heuristics.
double cMain::calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double)sqrt(
        (row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second)));
}
 
// A Utility Function to trace the path from the source
// to destination
void cMain::tracePath(cell cellDetails[][Dim], Pair dest)
{
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
 
    std::stack<Pair> Path;
 
    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col)) {
        Path.push(std::make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
 
    Path.push(std::make_pair(row, col));
    while (!Path.empty()) {
	std::pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
	cMain::SetArray(p.first, p.second, 10);
    	this->Update();
	this->Refresh(false);
	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		
    }
 
    return;
}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void cMain::aStarSearch(int grid[][Dim], Pair src, Pair dest)
{
    // If the source is out of range
    if (isValid(src.first, src.second) == false) {
        printf("Source is invalid\n");
        return;
    }
 
    // If the destination is out of range
    if (isValid(dest.first, dest.second) == false) {
        printf("Destination is invalid\n");
        return;
    }
 
    // Either the source or the destination is blocked
    if (isUnBlocked(grid , src.first, src.second) == false
        || isUnBlocked(grid , dest.first, dest.second)
               == false) {
        printf("Source or the destination is blocked\n");
        return;
    }
 
    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)
        == true) {
        printf("We are already at the destination\n");
        return;
    }

    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    bool closedList[Dim][Dim];
    memset(closedList, false, sizeof(closedList));
 
    // Declare a 2D array of structure to hold the details
    // of that cell
    cell cellDetails[Dim][Dim];
 
    int i, j;
 
    for (i = 0; i < Dim; i++) {
        for (j = 0; j < Dim; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }
 
    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
 
    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= Dim-1 & 0 <= j <= Dim-1
     This open list is implenented as a set of pair of
     pair.*/
    std::set<pPair> openList;
 
    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(std::make_pair(0.0, std::make_pair(i, j)));
 
    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDest = false;
 
    while (!openList.empty()) {
        pPair p = *openList.begin();
 
        // Remove this vertex from the open list
        openList.erase(openList.begin());
 
        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
 
        /*
         Generating all the 8 successor of this cell
 
             N.W   N   N.E
               \   |   /
                \  |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E
 
         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)*/
 
        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;
 
        //----------- 1st Successor (North) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j) == true) {
 
	    // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j] == false && isUnBlocked(grid , i - 1, j) == true) {
		
		cMain::SetArray(i - 1, j, 11);
		this->Update();
		this->Refresh(false);
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j].f == FLT_MAX
                    || cellDetails[i - 1][j].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i - 1, j)));
 
                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }
 
        //----------- 2nd Successor (South) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j) == true) {
             
	    // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j] == false && isUnBlocked(grid , i + 1, j) == true) {

		cMain::SetArray(i + 1, j, 11);    
			this->Update();
		this->Refresh(false);
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j].f == FLT_MAX
                    || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }
 
        //----------- 3rd Successor (East) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i, j + 1) == true) {
               

	    // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j + 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j + 1] == false
                     && isUnBlocked(grid , i, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
	    	cMain::SetArray(i, j + 1, 11);		
			this->Update();
		this->Refresh(false);
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j + 1].f == FLT_MAX
                    || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j + 1)));
 
                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }
 
        //----------- 4th Successor (West) ------------
 
        // Only process this cell if this is a valid one
        if (isValid(i, j - 1) == true) {
            
 
	    // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j - 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j - 1] == false
                     && isUnBlocked(grid , i, j - 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
	   	cMain::SetArray(i, j - 1, 11);		
			this->Update();
		this->Refresh(false);
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j - 1].f == FLT_MAX
                    || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j - 1)));
 
                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }
 
        //----------- 5th Successor (North-East)
        //------------
 
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j + 1) == true) {
            
 

	    // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j + 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j + 1].parent_i = i;
                cellDetails[i - 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j + 1] == false
                     && isUnBlocked(grid , i - 1, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
		cMain::SetArray(i - 1, j + 1, 11);		
			this->Update();
		this->Refresh(false);
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		hNew = calculateHValue(i - 1, j + 1, dest);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j + 1].f == FLT_MAX
                    || cellDetails[i - 1][j + 1].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i - 1, j + 1)));
 
                    // Update the details of this cell
                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                }
            }
        }
 
        //----------- 6th Successor (North-West)
        //------------
 
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j - 1) == true) {
            
		
	    // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j - 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j - 1].parent_i = i;
                cellDetails[i - 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j - 1] == false
                     && isUnBlocked(grid , i - 1, j - 1)
           == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j - 1, dest);
	    	cMain::SetArray(i - 1, j - 1, 11);		
			this->Update();
		this->Refresh(false);
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j - 1].f == FLT_MAX
                    || cellDetails[i - 1][j - 1].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i - 1, j - 1)));
                    // Update the details of this cell
                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                }
            }
        }
 
        //----------- 7th Successor (South-East)
        //------------
 
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j + 1) == true) {
 
	    // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j + 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j + 1].parent_i = i;
                cellDetails[i + 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j + 1] == false
                     && isUnBlocked(grid , i + 1, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j + 1, dest);
		fNew = gNew + hNew;
            	cMain::SetArray(i + 1, j + 1, 11);		
                	this->Update();
		this->Refresh(false);
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		// If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j + 1].f == FLT_MAX
                    || cellDetails[i + 1][j + 1].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i + 1, j + 1)));
 
                    // Update the details of this cell
                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                }
            }
        }
 
        //----------- 8th Successor (South-West)
        //------------
 
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j - 1) == true) {

	    // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j - 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j - 1].parent_i = i;
                cellDetails[i + 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j - 1] == false
                     && isUnBlocked(grid , i + 1, j - 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j - 1, dest);
                fNew = gNew + hNew;
		cMain::SetArray(i + 1, j - 1, 11);
                	this->Update();
		this->Refresh(false);
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		// If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j - 1].f == FLT_MAX
                    || cellDetails[i + 1][j - 1].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i + 1, j - 1)));
 
                    // Update the details of this cell
                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                }
            }
        }
    }
 
    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destiantion cell. This may happen when the
    // there is no way to destination cell (due to
    // blockages)
    if (foundDest == false)
    {
        printf("Failed to find the Destination Cell\n");
 
    return;
    }
	
	//wxWindow::Refresh();
	this->Refresh(false);
}

/* 
// Driver program to test above function
int main()
{
    //Description of the Grid-
    // 0--> The cell is not blocked
    // 1--> The cell is blocked    
    int grid[Dim][Dim]
        = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };
 
    // Source is the left-most bottom-most corner
    Pair src = std::make_pair(8, 0);
 
    // Destination is the left-most top-most corner
    Pair dest = std::make_pair(0, 0);
 
    aStarSearch(grid, src, dest);
 
    return (0);
}
*/
