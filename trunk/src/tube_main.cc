//-----------------------------------------------------------------------------
// Name:        tube_main.cc
// Purpose:     jhxTube: not physical correct, but realistic realtime
//				simulation of flexible tubes : main program file
// Author:      Jahn Fuchs (jhx) - jahn@jhx.de
// Copyright:   (c) Jahn Fuchs
// Licence:     GPL
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GCC implementation
//-----------------------------------------------------------------------------
#ifdef __GNUG__
    #pragma implementation "tube_main.h"
#endif

//-----------------------------------------------------------------------------
// Standard wxWidgets headers

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif


// For all others, include the necessary (standard) headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

//-----------------------------------------------------------------------------
// Header of this file
//-----------------------------------------------------------------------------

#include "tube_main.h"

//-----------------------------------------------------------------------------
// Needed wx headers, then wx/contrib headers, then application headers
//-----------------------------------------------------------------------------

#include "wx/intl.h"				// Internationalisation
#include "wx/image.h"               // wxImage
#include "wx/filesys.h"				// File System
#include "wx/fs_zip.h"				// Zip File System
//-----------------------------------------------------------------------------
#include "wx/xrc/xmlres.h"          // XRC XML resouces
//-----------------------------------------------------------------------------
#include "tube_frame.h"

//-----------------------------------------------------------------------------
// wxWidgets macro: Declare the application.
//-----------------------------------------------------------------------------
IMPLEMENT_APP(TubeApp)

//-----------------------------------------------------------------------------
// Public methods
//-----------------------------------------------------------------------------

bool TubeApp::OnInit()
{
	// also look in "lang" subdir for translations
    wxLocale::AddCatalogLookupPathPrefix
		( wxT(wxString("..") + wxFILE_SEP_PATH + wxString("lang")));

	m_locale = NULL;
	SelectLanguage( wxLANGUAGE_DEFAULT );

	// Image handler
    wxImage::AddHandler(new wxXPMHandler);
    wxImage::AddHandler(new wxPNGHandler);
    //Zip File Handler (for XRS resource files)
	wxFileSystem::AddHandler(new wxZipFSHandler);

    // Initialize all the XRC handlers.
    wxXmlResource::Get()->InitAllHandlers();

    // Load the XML resource files
    wxXmlResource::Get()->Load(wxT("resource.xrs"));

    // Make an instance of the derived frame.
    TubeFrame *frame = new TubeFrame();
    frame->Show(true); // Show the frame.

    // Return true (tell program to continue) (false would terminate).
    return true;
}

void TubeApp::SelectLanguage(int lang)
{
	delete m_locale;
	m_locale = new wxLocale( lang );
	m_locale->AddCatalog( wxT("jhxtube") );
}

TubeApp::~TubeApp()
{
	delete m_locale;
}
