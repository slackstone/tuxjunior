//  $Id: snowball.cpp 4435 2006-11-04 14:13:27Z sommer $
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

#include <config.h>

#include "snowball.hpp"

SnowBall::SnowBall(const lisp::Lisp& reader)
    : WalkingBadguy(reader, "images/creatures/snowball/snowball.sprite", "left", "right")
{
  walk_speed = 80;
}

SnowBall::SnowBall(const Vector& pos, Direction d)
    : WalkingBadguy(pos, d, "images/creatures/snowball/snowball.sprite", "left", "right")
{
  walk_speed = 80;
}

void
SnowBall::write(lisp::Writer& writer)
{
  writer.start_list("snowball");
  WalkingBadguy::write(writer);
  writer.end_list("snowball");
}

bool
SnowBall::collision_squished(GameObject& object)
{
  sprite->set_action(dir == LEFT ? "squished-left" : "squished-right");
  kill_squished(object);
  return true;
}

IMPLEMENT_FACTORY(SnowBall, "snowball")
