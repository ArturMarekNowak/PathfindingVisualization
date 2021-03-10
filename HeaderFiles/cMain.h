//GUI starte
//Contains structure and implementation of event handlers
#include "wx/wx.h"
#include <array>
#include "Astar.h"

#define Dim 20

class cMain : public wxMDIParentFrame
{
	public: 
		cMain();
		~cMain();
			
		void SetColour(int & c);
		void SetArray(int row, int col, int c);
		void SetSrc(int i, int j);
		void SetDst(int i, int j);
		
		int GetColour();
		int GetArray(int row, int col);
		Pair GetDst();
		Pair GetSrc();

	private:
		static Pair m_src;
		static Pair m_dst;
		const int m_gridDim = Dim;
		const int m_pixelSize = 20;		
		static int m_colour;
		static int m_arrayOfColours[20][20];

		wxToolBar *m_ToolBar = nullptr;
		wxMenuBar *m_MenuBar = nullptr;

		void OnMenuReset(wxCommandEvent &evt);
		void OnMenuExit(wxCommandEvent &evt);
		
		void OnButtonClick(wxCommandEvent &evt);
		void OnMouseClick(wxMouseEvent &evt);

		void OnDraw(wxDC & dc);
		void OnPaint(wxPaintEvent & evt);

		wxDECLARE_EVENT_TABLE();	
};
