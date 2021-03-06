// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: m_swap.c,v 1.1 2005/12/20 19:11:56 sfxgligli Exp $
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
// $Log: m_swap.c,v $
// Revision 1.1  2005/12/20 19:11:56  sfxgligli
// - added Doom port
// - Gmini400 buttons fix
//
//
// DESCRIPTION:
//	Endianess handling, swapping 16bit and 32bit.
//
//-----------------------------------------------------------------------------

static const char
rcsid[] = "$Id: m_swap.c,v 1.1 2005/12/20 19:11:56 sfxgligli Exp $";


#ifdef __GNUG__
#pragma implementation "m_swap.h"
#endif
#include "m_swap.h"


// Swap 16bit, that is, MSB and LSB byte.
unsigned short SwapSHORT(unsigned short x)
{
    // No masking with 0xFF should be necessary. 
    return (x>>8) | (x<<8);
}

// Swapping 32bit.
unsigned long SwapLONG( unsigned long x)
{
    return
	(x>>24)
	| ((x>>8) & 0xff00)
	| ((x<<8) & 0xff0000)
	| (x<<24);
}


