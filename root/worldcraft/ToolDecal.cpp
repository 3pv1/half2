//========= Copyright � 1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "stdafx.h"
#include "GlobalFunctions.h"
#include "History.h"
#include "MapDoc.h"
#include "MapDecal.h"
#include "MapSolid.h"
#include "MapView3D.h"
#include "resource.h"
#include "ToolManager.h"
#include "ToolDecal.h"


//-----------------------------------------------------------------------------
// Purpose: Handles key down events in the 2D view.
// Input  : Per CWnd::OnKeyDown. 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CToolDecal::OnKeyDown2D(CMapView2D *pView, UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
		case VK_ESCAPE:
		{
			g_pToolManager->SetTool(TOOL_POINTER);
			return true;
		}
	}
	
	return false;
}


//-----------------------------------------------------------------------------
// Purpose: Handles mouse move events in the 2D view.
// Input  : Per CWnd::OnMouseMove.
// Output : Returns true if the message was handled, false if not.
//-----------------------------------------------------------------------------
bool CToolDecal::OnMouseMove2D(CMapView2D *pView, UINT nFlags, CPoint point) 
{
	SetDecalCursor();
	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Handles key down events in the 3D view.
// Input  : Per CWnd::OnKeyDown.
// Output : Returns true if the message was handled, false if not.
//-----------------------------------------------------------------------------
bool CToolDecal::OnKeyDown3D(CMapView3D *pView, UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_ESCAPE:
		{
			g_pToolManager->SetTool(TOOL_POINTER);
		}
	}

	return false;
}


//-----------------------------------------------------------------------------
// Purpose: Handles left button down events in the 3D view. 
// Input  : Per CWnd::OnLButtonDown.
// Output : Returns true if the message was handled, false if not.
//-----------------------------------------------------------------------------
bool CToolDecal::OnLMouseDown3D(CMapView3D *pView, UINT nFlags, CPoint point) 
{
	//
	// See if they clicked on a brush face. If so, apply a decal where they clicked.
	//
	CMapDoc *pDoc = pView->GetDocument();

	ULONG ulFace;
	CMapClass *pObject;

	if ((pObject = pView->NearestObjectAt(point, ulFace)) != NULL)
	{
		CMapSolid *pSolid = dynamic_cast <CMapSolid *> (pObject);
		if (pSolid == NULL)
		{
			return true;
		}

		//
		// Build a ray to trace against the face that they clicked on to
		// find the point of intersection.
		//			
		Vector Start;
		Vector End;
		pView->BuildRay(point, Start, End);

		Vector HitPos, HitNormal;
		CMapFace *pFace = pSolid->GetFace(ulFace);
		if (pFace->TraceLine(HitPos, HitNormal, Start, End))
		{
			GetHistory()->MarkUndoPosition(NULL, "Create decal");

			CMapEntity *pEntity = new CMapEntity;
			pEntity->SetKeyValue("texture", GetDefaultTextureName());
			pEntity->SetPlaceholder(TRUE);
			pEntity->SetOrigin(HitPos);
			pEntity->SetClass("infodecal");

			CMapWorld *pWorld = pDoc->GetMapWorld();

			CMapDecal *pDecal = pEntity->GetChildOfType((CMapDecal *)NULL);
			if (pDecal != NULL)
			{
				pDecal->DecalAllSolids(pWorld);
			}

			pEntity->CalcBounds(TRUE);
			pDoc->AddObjectToWorld(pEntity);

			GetHistory()->KeepNew(pEntity);

			UpdateBox ub;
			CMapObjectList ObjectList;
			ObjectList.AddTail(pEntity);
			ub.Objects = &ObjectList;

			Vector mins;
			Vector maxs;
			pEntity->GetRender2DBox(mins, maxs);
			ub.Box.SetBounds(mins, maxs);

			pDoc->UpdateAllViews(NULL, MAPVIEW_UPDATE_OBJECTS, &ub);

			pDoc->SetModifiedFlag();
		}
	}

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Handles mouse move events in the 3D view.
// Input  : Per CWnd::OnMouseMove.
// Output : Returns true if the message was handled, false if not.
//-----------------------------------------------------------------------------
bool CToolDecal::OnMouseMove3D(CMapView3D *pView, UINT nFlags, CPoint point)
{
	SetDecalCursor();
	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Sets the cursor to the decal application cursor.
//-----------------------------------------------------------------------------
void CToolDecal::SetDecalCursor(void)
{
	static HCURSOR hcurDecal;
	
	if (!hcurDecal)
	{
		hcurDecal = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_DECAL));
	}
	
	SetCursor(hcurDecal);
}
