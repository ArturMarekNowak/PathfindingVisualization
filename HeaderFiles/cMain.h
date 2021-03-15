//GUI starte
//Contains structure and implementation of event handlers
#include "wx/wx.h"
#include <array>
#include <bits/stdc++.h>


#define Dim 20

// Creating a shortcut for int, int pair type
typedef std::pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef std::pair<double, std::pair<int, int>> pPair;

// A structure to hold the neccesary parameters
struct cell {
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= Dim-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

bool isValid(int row, int col);

bool isUnBlocked(int grid[][Dim], int row, int col);

bool isDestination(int row, int col, Pair dest);

double calculateHValue(int row, int col, Pair dest);

void tracePath(cell cellDetails[][Dim], Pair dest);

void aStarSearch(int grid[][Dim], Pair src, Pair dest);



class cMain : public wxMDIParentFrame
{
	public: 
		cMain();
		~cMain();

		int (*GetWholeArray())[Dim];	

		void SetColour(int & c);
		void SetArray(int row, int col, int c);
		void SetSrc(int i, int j);
		void SetDst(int i, int j);
		
		int GetSrcFirst();
		int GetSrcSecond();

		int GetDstFirst();
		int GetDstSecond();

		const int GetGridDim();
		const int GetPixelSize();		

		int GetColour();
		int GetArray(int row, int col);
		Pair GetDst();
		Pair GetSrc();

	private:
		static Pair m_src;
		static Pair m_dst;
		const int m_gridDim = Dim;
		const int m_pixelSize = Dim;		
		static int m_colour;
		static int m_arrayOfColours[Dim][Dim];

		wxToolBar *m_ToolBar = nullptr;
		wxMenuBar *m_MenuBar = nullptr;

		void OnMenuReset(wxCommandEvent &evt);
		void OnMenuExit(wxCommandEvent &evt);
		
		void OnButtonClick(wxCommandEvent &evt);
		void OnMouseClick(wxMouseEvent &evt);

		void OnDraw(wxDC & dc);
		void OnPaint(wxPaintEvent & evt);

		wxDECLARE_EVENT_TABLE();	
		
		bool isValid(int row, int col);

		bool isUnBlocked(int grid[][Dim], int row, int col);

		bool isDestination(int row, int col, Pair dest);

		double calculateHValue(int row, int col, Pair dest);

		void tracePath(cell cellDetails[][Dim], Pair dest);

		void aStarSearch(int grid[][Dim], Pair src, Pair dest);

};
