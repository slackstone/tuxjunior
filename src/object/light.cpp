//  $Id: light.cpp 4238 2006-09-17 15:02:05Z sommer $
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

#include "light.hpp"
#include "sprite/sprite_manager.hpp"
#include "resources.hpp"
#include "video/drawing_context.hpp"
#include "object_factory.hpp"
#include "player.hpp"
#include "sector.hpp"

Light::Light(const Vector& center, const Color& color) : position(center), color(color)
{
  sprite = sprite_manager->create("images/objects/lightmap_light/lightmap_light.sprite");
}

Light::~Light()
{
  delete sprite;
}

void
Light::update(float )
{
}

void
Light::draw(DrawingContext& context)
{
  context.push_target();
  context.set_target(DrawingContext::LIGHTMAP);

  sprite->set_color(color);
  sprite->set_blend(Blend(GL_SRC_ALPHA, GL_ONE));
  sprite->set_angle(90); // FIXME: color won't get applied for angle=0
  sprite->draw(context, position, 0);

  context.pop_target();
}

