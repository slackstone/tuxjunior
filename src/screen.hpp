//  $Id: screen.hpp 5235 2007-12-26 01:54:49Z sommer $
//
//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

class DrawingContext;

/**
 * Abstract base class for code the MainLoop runs exclusively and full-screen.
 *
 * Examples of Screens are: The TitleScreen, a WorldMap, a level's 
 * GameSession, a TextScroller, ...
 */
class Screen
{
public:
  virtual ~Screen()
  {}

  /**
   * gets called before this screen gets activated (which is at least once
   * before the first draw or update call
   */
  virtual void setup()
  {}
  /** gets called when the current screen is temporarily suspended */
  virtual void leave()
  {}

  /**
   * gets called once per frame. The screen should draw itself in this function.
   * State changes should not be done in this function, but rather in update
   */
  virtual void draw(DrawingContext& context) = 0;

  /**
   * gets called for once (per logical) frame. Screens should do their state
   * updates and logic here
   */
  virtual void update(float elapsed_time) = 0;
};

#endif
