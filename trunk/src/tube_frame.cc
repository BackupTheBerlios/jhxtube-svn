//-----------------------------------------------------------------------------
// Name:        tube_frame.cc
// Purpose:     jhxTube: not physical correct, but realistic realtime
//				simulation of flexible tubes : main frame file
// Author:      Jahn Fuchs (jhx) - jahn@jhx.de
// Copyright:   (c) Jahn Fuchs
// Licence:     GPL
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GCC implementation
//-----------------------------------------------------------------------------
#ifdef __GNUG__
    #pragma implementation "tube_frame.h"
#endif

//-----------------------------------------------------------------------------
// Standard wxWidgets headers
//-----------------------------------------------------------------------------

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
#include "tube_frame.h"

//-----------------------------------------------------------------------------
// Needed wx headers, then wx/contrib headers, then application headers
//-----------------------------------------------------------------------------

#include "wx/image.h"               // wxImage
#include "wx/filesys.h"				// File System
#include "wx/fs_zip.h"				// Zip File System
//-----------------------------------------------------------------------------
#include "wx/xrc/xmlres.h"          // XRC XML resouces
//-----------------------------------------------------------------------------

// The application icon. Non-MSW platforms use an xpm. MSW uses an .ico file
#if defined(__WXGTK__) || defined(__WXX11__) || defined(__WXMOTIF__) || defined(__WXMAC__) || defined(__WXMGL__)
    #include "appicon.xpm"
#endif

//-----------------------------------------------------------------------------
// Event table: connect the events to the handler functions to process them
//-----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(TubeFrame, wxFrame)
    EVT_MENU(XRCID("exit_menuitem"),  TubeFrame::OnExitCommand)
    EVT_MENU(XRCID("about_menuitem"), TubeFrame::OnAboutCommand)
    EVT_MENU(XRCID("sel_language_menuitem"), TubeFrame::OnLanguageSelectCommand)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
// Public methods
//-----------------------------------------------------------------------------

// Constructor
TubeFrame::TubeFrame(wxWindow* parent)//, wxLocale& locale):m_locale(locale)
{

    // Load up this frame from XRC.
    wxXmlResource::Get()->LoadFrame(this, parent, wxT("tube_frame"));

    //SetIcon(wxXmlResource::Get()->LoadIcon(wxT("appicon.xpm")));
    SetMenuBar(wxXmlResource::Get()->LoadMenuBar(wxT("tube_menubar")));
    //wxFrame *frame2 = new wxFrame();
    //wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    //SetSizer(topSizer);
    //topSizer->Add(frame2);

}


//-----------------------------------------------------------------------------
// Private methods
//-----------------------------------------------------------------------------

void TubeFrame::RepaintStrings()
{
	SetMenuBar(wxXmlResource::Get()->LoadMenuBar(wxT("tube_menubar")));

}

void TubeFrame::OnExitCommand(wxCommandEvent& WXUNUSED(event))
{
    Close(true); // true is to force the frame to close.
}

void TubeFrame::OnAboutCommand(wxCommandEvent& WXUNUSED(event))
{
    wxDialog dlg; wxStaticText* label;
    wxXmlResource::Get()->LoadDialog(&dlg, this, wxT("about_dialog"));
    label = XRCCTRL(*this,"label_about_version",wxStaticText);
    label->SetLabel(wxString(_("THIS IS A BETA VERSION. DO...")));
    dlg.ShowModal();
}

void TubeFrame::OnLanguageSelectCommand(wxCommandEvent& WXUNUSED(event))
{
    wxArrayInt languageCodes;
    wxArrayString languageNames;

    languageCodes.Add(wxLANGUAGE_ENGLISH);
    languageNames.Add(_("English"));
    //languageCodes.Add(wxLANGUAGE_FRENCH);
    //languageNames.Add(_("French"));
    languageCodes.Add(wxLANGUAGE_GERMAN);
    languageNames.Add(_("German"));

    int lang = wxGetSingleChoiceIndex(_("Select Language:"),
										_("Language"),languageNames);
	if (lang != -1 )
	{
		wxGetApp().SelectLanguage(languageCodes[lang]);
		RepaintStrings();
	}
}




TubeGLCanvas::TubeGLCanvas(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name)
    : wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name)
{
    //block = false;
}
TubeGLCanvas::~TubeGLCanvas()
{
    /* destroy mesh */
    //lw_object_free(info.lwobject);
}


