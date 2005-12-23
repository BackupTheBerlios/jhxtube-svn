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
	// Set main window size
    SetSize(550,400);

	// get the Pointer on the glpanel resource
	wxPanel* glpanel = XRCCTRL(*this,wxT("glpanel"),wxPanel);
	// automatically take care of Constraints in OnSize();
	glpanel->SetAutoLayout(true);
	// Create GLCanvas on "glpanel"
 	this->SetCanvas( new TubeGLCanvas( glpanel, wxID_ANY,
					 wxDefaultPosition, glpanel->GetSize(), wxSUNKEN_BORDER) );

	wxLayoutConstraints *c = new wxLayoutConstraints;
	c->left.SameAs( glpanel, wxLeft );
	c->height.SameAs( glpanel, wxHeight );
	c->top.SameAs( glpanel, wxTop );
	c->right.SameAs( glpanel, wxRight );
	// Set the constraints for our GLCanvas
	this->m_canvas->SetConstraints( c );

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
    label = XRCCTRL(*this,wxT("label_about_version"),wxStaticText);
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



//----------------------- TUBE GL CANVAS -------------------------------------


BEGIN_EVENT_TABLE(TubeGLCanvas, wxGLCanvas)
    EVT_PAINT(TubeGLCanvas::OnPaint)
    EVT_ENTER_WINDOW( TubeGLCanvas::OnEnterWindow )
    EVT_SIZE(TubeGLCanvas::OnSize)
    EVT_ERASE_BACKGROUND(TubeGLCanvas::OnEraseBackground)
END_EVENT_TABLE()


TubeGLCanvas::TubeGLCanvas(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name)
    : wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name)
{
    //block = false;
}
TubeGLCanvas::~TubeGLCanvas()
{}

void TubeGLCanvas::OnEnterWindow( wxMouseEvent& WXUNUSED(event) )
{
    SetFocus();
}

void TubeGLCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    Render();
}

void TubeGLCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
  // Do nothing, to avoid flashing.
}

void TubeGLCanvas::OnSize(wxSizeEvent& event)
{
    // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);
    // set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
    int w, h;
    GetParent()->GetSize(&w, &h);

#ifndef __WXMOTIF__
    if (GetContext())
#endif
    {
        SetCurrent();
        glViewport(0, 0, (GLint) w, (GLint) h);
    }
}


void TubeGLCanvas::InitGL()
{
    SetCurrent();

    /* set viewing projection */
    glMatrixMode(GL_PROJECTION);
    glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);

    /* position viewer */
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.0f, 0.0f, -2.0f);

    /* position object */
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


void TubeGLCanvas::Render()  // example Render() function
{
    wxPaintDC dc(this);

#ifndef __WXMOTIF__
    if (!GetContext()) return;
#endif

    SetCurrent();
    // Init OpenGL once, but after SetCurrent
    if (!m_init)
    {
        InitGL();
        m_init = true;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);
    glMatrixMode(GL_MODELVIEW);

    /* clear color and depth buffers */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if( m_gllist == 0 )
    {
        m_gllist = glGenLists( 1 );
        glNewList( m_gllist, GL_COMPILE_AND_EXECUTE );
        /* draw six faces of a cube */
        glBegin(GL_QUADS);
        glNormal3f( 0.0f, 0.0f, 1.0f);
        glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f,-0.5f, 0.5f); glVertex3f( 0.5f,-0.5f, 0.5f);

        glNormal3f( 0.0f, 0.0f,-1.0f);
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f, 0.5f,-0.5f);
        glVertex3f( 0.5f, 0.5f,-0.5f); glVertex3f( 0.5f,-0.5f,-0.5f);

        glNormal3f( 0.0f, 1.0f, 0.0f);
        glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f( 0.5f, 0.5f,-0.5f);
        glVertex3f(-0.5f, 0.5f,-0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);

        glNormal3f( 0.0f,-1.0f, 0.0f);
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f( 0.5f,-0.5f,-0.5f);
        glVertex3f( 0.5f,-0.5f, 0.5f); glVertex3f(-0.5f,-0.5f, 0.5f);

        glNormal3f( 1.0f, 0.0f, 0.0f);
        glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f( 0.5f,-0.5f, 0.5f);
        glVertex3f( 0.5f,-0.5f,-0.5f); glVertex3f( 0.5f, 0.5f,-0.5f);

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f,-0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f,-0.5f);
        glEnd();

        glEndList();
    }
    else
    {
        glCallList(m_gllist);
    }

    glFlush();
    SwapBuffers();
}

