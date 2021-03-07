#include "Pathfinding.h"

wxIMPLEMENT_APP(pathfindingApp);

pathfindingApp::pathfindingApp()
{

}

pathfindingApp::~pathfindingApp()
{

}

bool pathfindingApp::OnInit()
{
	m_frame1 = new cMain();
	m_frame1->Show();
	return true;
}
