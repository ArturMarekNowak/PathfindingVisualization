//GUI starte
//Contains structure and implementation of event handlers
#include "wx/wx.h"

class cMain : public wxMDIParentFrame
{
	public: 
		cMain();
		~cMain();

	private:
		wxToolBar *m_ToolBar = nullptr;
		wxMenuBar *m_MenuBar = nullptr;

		void OnMenuReset(wxCommandEvent &evt);
		void OnMenuExit(wxCommandEvent &evt);
		
		void OnButtonClick(wxCommandEvent &evt);

		wxDECLARE_EVENT_TABLE();	
};
