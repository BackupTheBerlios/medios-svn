// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// $Id: i_main.c,v 1.3 2006/02/08 17:45:40 oxygen77 Exp $
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log: i_main.c,v $
// Revision 1.3  2006/02/08 17:45:40  oxygen77
// big cleanup in makefiles
//
// Revision 1.2  2006/02/06 22:45:48  oxygen77
// make doom work with new api, we lack of exit() now
//
// Revision 1.1  2005/12/20 19:11:56  sfxgligli
// - added Doom port
// - Gmini400 buttons fix
//
//
// DESCRIPTION:
//	Main program, simply calls D_DoomMain high level loop.
//
//-----------------------------------------------------------------------------

static const char
rcsid[] = "$Id: i_main.c,v 1.3 2006/02/08 17:45:40 oxygen77 Exp $";


#include "doomdef.h"

#include "m_argv.h"
#include "d_main.h"

int app_main(){
    myargc = 0;
    myargv = NULL;

    D_DoomMain ();

    return 0;
} 
