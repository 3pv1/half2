//========= Copyright ? 1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "ServerListCompare.h"
#include "server.h"
#include "ServerBrowserDialog.h"

#include <KeyValues.h>
#include <vgui_controls/ListPanel.h>

//-----------------------------------------------------------------------------
// Purpose: List password column sort function
//-----------------------------------------------------------------------------
int __cdecl PasswordCompare(const void *elem1, const void *elem2 )
{
	vgui::ListPanelItem *p1, *p2;
	p1 = *(vgui::ListPanelItem **)elem1;
	p2 = *(vgui::ListPanelItem **)elem2;

	if ( !p1 || !p2 )  // No meaningful comparison
	{
		return 0;  
	}

	serveritem_t &s1 = ServerBrowserDialog().GetServer(p1->userData);
	serveritem_t &s2 = ServerBrowserDialog().GetServer(p2->userData);

	if (s1.password < s2.password)
		return 1;
	else if (s1.password > s2.password)
		return -1;

	return 0;
}

//-----------------------------------------------------------------------------
// Purpose: Ping comparison function
//-----------------------------------------------------------------------------
int __cdecl PingCompare(const void *elem1, const void *elem2 )
{
	vgui::ListPanelItem *p1, *p2;
	p1 = *(vgui::ListPanelItem **)elem1;
	p2 = *(vgui::ListPanelItem **)elem2;

	if ( !p1 || !p2 )  // No meaningful comparison
	{
		return 0;  
	}

	serveritem_t &s1 = ServerBrowserDialog().GetServer(p1->userData);
	serveritem_t &s2 = ServerBrowserDialog().GetServer(p2->userData);

	int ping1 = s1.ping;
	int ping2 = s2.ping;

	if ( ping1 < ping2 )
		return -1;
	else if ( ping1 > ping2 )
		return 1;
	
	return 0;
}

//-----------------------------------------------------------------------------
// Purpose: Map comparison function
//-----------------------------------------------------------------------------
int __cdecl MapCompare(const void *elem1, const void *elem2 )
{
	vgui::ListPanelItem *p1, *p2;
	p1 = *(vgui::ListPanelItem **)elem1;
	p2 = *(vgui::ListPanelItem **)elem2;

	if ( !p1 || !p2 )  // No meaningful comparison
	{
		return 0;  
	}

	serveritem_t &s1 = ServerBrowserDialog().GetServer(p1->userData);
	serveritem_t &s2 = ServerBrowserDialog().GetServer(p2->userData);

	return stricmp(s1.map, s2.map);
}

//-----------------------------------------------------------------------------
// Purpose: Game dir comparison function
//-----------------------------------------------------------------------------
int __cdecl GameCompare(const void *elem1, const void *elem2 )
{
	vgui::ListPanelItem *p1, *p2;
	p1 = *(vgui::ListPanelItem **)elem1;
	p2 = *(vgui::ListPanelItem **)elem2;

	if ( !p1 || !p2 )  // No meaningful comparison
	{
		return 0;  
	}

	serveritem_t &s1 = ServerBrowserDialog().GetServer(p1->userData);
	serveritem_t &s2 = ServerBrowserDialog().GetServer(p2->userData);

	// make sure we haven't added the same server to the list twice
	Assert(p1->userData != p2->userData);

	return stricmp(s1.gameDescription, s2.gameDescription);
}

//-----------------------------------------------------------------------------
// Purpose: Server name comparison function
//-----------------------------------------------------------------------------
int __cdecl ServerNameCompare(const void *elem1, const void *elem2 )
{
	vgui::ListPanelItem *p1, *p2;
	p1 = *(vgui::ListPanelItem **)elem1;
	p2 = *(vgui::ListPanelItem **)elem2;

	if ( !p1 || !p2 )  // No meaningful comparison
	{
		return 0;  
	}

	serveritem_t &s1 = ServerBrowserDialog().GetServer(p1->userData);
	serveritem_t &s2 = ServerBrowserDialog().GetServer(p2->userData);

	return stricmp(s1.name, s2.name);
}

//-----------------------------------------------------------------------------
// Purpose: Player number comparison function
//-----------------------------------------------------------------------------
int __cdecl PlayersCompare(const void *elem1, const void *elem2 )
{
	vgui::ListPanelItem *p1, *p2;
	p1 = *(vgui::ListPanelItem **)elem1;
	p2 = *(vgui::ListPanelItem **)elem2;

	if ( !p1 || !p2 )  // No meaningful comparison
	{
		return 0;  
	}

	serveritem_t &s1 = ServerBrowserDialog().GetServer(p1->userData);
	serveritem_t &s2 = ServerBrowserDialog().GetServer(p2->userData);

	int s1p = s1.players;
	int s1m = s1.maxPlayers;
	int s2p = s2.players;
	int s2m = s2.maxPlayers;

	// compare number of players
	if (s1p > s2p)
		return -1;
	if (s1p < s2p)
		return 1;

	// compare max players if number of current players is equal
	if (s1m > s2m)
		return -1;
	if (s1m < s2m)
		return 1;

	return 0;
}


