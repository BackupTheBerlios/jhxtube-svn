//-----------------------------------------------------------------------------
// Name:        tube_frame.cc
// Purpose:     jhxTube: not physical correct, but realistic realtime
//				simulation of flexible tubes : main frame file
// Author:      Jahn Fuchs (jhx) - jahn@jhx.de
// Copyright:   (c) Jahn Fuchs
// Licence:     GPL
//-----------------------------------------------------------------------------

// Begin single inclusion
#ifndef _TUBE_FRAME_H_
#define _TUBE_FRAME_H_
#if !wxUSE_GLCANVAS
    #error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif
//-----------------------------------------------------------------------------
// GCC interface
//-----------------------------------------------------------------------------
#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "myframe.h"
#endif

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------
#include "wx/glcanvas.h"
#include "wx/frame.h"

class TubeGLCanvas;

//-----------------------------------------------------------------------------
// Class definition: TubeFrame
//-----------------------------------------------------------------------------

// Define a new frame type: this is going to be our main frame
class TubeFrame : public wxFrame
{

public:
    // Constructor.
    TubeFrame( wxWindow* parent=(wxWindow *)NULL);

    void SetCanvas( TubeGLCanvas *canvas ) { m_canvas = canvas; }
    TubeGLCanvas *GetCanvas() { return m_canvas; }

private:
	TubeGLCanvas *m_canvas;
	void RepaintStrings();

    // Event handlers (these functions should _not_ be virtual)
    void OnExitCommand(wxCommandEvent& event);
    void OnAboutCommand(wxCommandEvent& event);
    void OnLanguageSelectCommand(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};



class TubeGLCanvas: public wxGLCanvas
{
public:
	TubeGLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize, long style = 0,
			const wxString& name = wxT("TubeGLCanvas"));

    ~TubeGLCanvas();

    void OnPaint(wxPaintEvent& event);
    void OnEnterWindow(wxMouseEvent& event);
	void OnSize(wxSizeEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
	void Render();
    void InitGL();

private:
    bool   m_init;
    GLuint m_gllist;
    long   m_rleft;
    long   m_rright;

    static unsigned long  m_secbase;
    static int            m_TimeInitialized;
    static unsigned long  m_xsynct;
    static unsigned long  m_gsynct;

    long           m_Key;
    unsigned long  m_StartTime;
    unsigned long  m_LastTime;
    unsigned long  m_LastRedraw;

    DECLARE_EVENT_TABLE()
};



// End single inclusion
#endif  // _TUBE_FRAME_H_
