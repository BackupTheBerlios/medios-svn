// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: p_tick.h,v 1.1 2005/12/20 19:11:56 sfxgligli Exp $
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
// DESCRIPTION:
//	?
//
//-----------------------------------------------------------------------------


#ifndef __P_TICK__
#define __P_TICK__


#ifdef __GNUG__
#pragma interface
#endif


// Called by C_Ticker,
// can call G_PlayerExited.
// Carries out all thinking of monsters and players.
void P_Ticker (void);



#endif
//-----------------------------------------------------------------------------
//
// $Log: p_tick.h,v $
// Revision 1.1  2005/12/20 19:11:56  sfxgligli
// - added Doom port
// - Gmini400 buttons fix
//
//
//-----------------------------------------------------------------------------
