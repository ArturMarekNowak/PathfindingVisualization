//Launcher
#include "wx/wx.h"
#include "cMain.h"

class pathfindingApp : public wxApp
{

	public:
		pathfindingApp();
		~pathfindingApp();

	private: 
		cMain* m_frame1 = nullptr;

	public:
		virtual bool OnInit();
};

