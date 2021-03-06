/*
 * $Id: DockedHandler.cs 4703 2007-01-28 13:44:03Z anmaster $
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
	public delegate void DockedHandler (object o, DockedArgs args);

	public class DockedArgs : EventArgs {
		private DockObject requestor;
		private DockPlacement position;

		public DockedArgs (DockObject requestor, DockPlacement position)
		{
			this.requestor = requestor;
			this.position = position;
		}

		public DockObject Requestor {
			get {
				return requestor;
			}
		}

		public DockPlacement Position {
			get {
				return position;
			}
		}
	}
}
