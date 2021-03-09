//GUI starte
//Contains structure and implementation of event handlers
#include "wx/wx.h"

#define Dim 20

class cMain : public wxMDIParentFrame
{
	public: 
		cMain();
		~cMain();
			
		void SetColour(int & c);
		void SetArray(int row, int col, int c);
		int GetColour();
		int GetArray(int row, int col);

	private:
		const int m_gridDim = Dim;
		const int m_pixelSize = 20;		
		static int m_colour;
		int m_arrayOfColours[Dim][Dim] = {0};

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
