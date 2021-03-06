/*
 * $Id: DockObjectFlags.cs 4703 2007-01-28 13:44:03Z anmaster $
 *
 * Copyright (C) 2004 Todd Berman <tberman@off.net>
 * Copyright (C) 2004 Jeroen Zwartepoorte <jeroen@xs4all.nl>
 * Copyright (C) 2005 John Luke <john.luke@gmail.com>
 *
 * based on work by:
 * Copyright (C) 2002 Gustavo Giráldez <gustavo.giraldez@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
using System;

namespace Gdl
{
	[Serializable]
	[Flags]
	public enum DockObjectFlags
	{
		Automatic = 1 << 0,
		Attached = 1 << 1,
		InReflow = 1 << 2,
		InDetach = 1 << 3,
		InDrag = 1 << 4,
		InPreDrag = 1 << 5,
		Iconified = 1 << 6,
		UserAction = 1 << 7
	}
}
