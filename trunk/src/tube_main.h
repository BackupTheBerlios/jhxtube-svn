//-----------------------------------------------------------------------------
// Name:        tube_main.h
// Purpose:     jhxTube: not physical correct, but realistic realtime
//				simulation of flexible tubes : main program header file
// Author:      Jahn Fuchs (jhx) - jahn@jhx.de
// Copyright:   (c) Jahn Fuchs
// Licence:     GPL
//-----------------------------------------------------------------------------

// Single inclusion of this .h file
#ifndef _TUBE_MAIN_H_
#define _TUBE_MAIN_H_

//-----------------------------------------------------------------------------
// GCC interface
//-----------------------------------------------------------------------------
#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "tube_main.h"
#endif

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------
#include "wx/app.h"             // wxApp

//-----------------------------------------------------------------------------
// Class definition: TubeApp
//-----------------------------------------------------------------------------

class TubeApp : public wxApp
{

public:
	~TubeApp();				 //destructor
    virtual bool OnInit();
    void SelectLanguage(int lang);
private:
    wxLocale* m_locale;
};

DECLARE_APP(TubeApp)

// End single inclusion of this .h file
#endif  //_TUBE_MAIN_H_
