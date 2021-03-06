//  $Id: sprite_particle.hpp 4063 2006-07-21 21:05:23Z anmaster $
//
//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//  Copyright (C) 2006 Christoph Sommer <christoph.sommer@2006.expires.deltadevelopment.de>
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

#ifndef __SPRITE_PARTICLE_H__
#define __SPRITE_PARTICLE_H__


#include "game_object.hpp"
#include "resources.hpp"
#include "player.hpp"
#include "object/anchor_point.hpp"
#include "sprite/sprite.hpp"
#include "sprite/sprite_manager.hpp"
#include "video/drawing_context.hpp"

class SpriteParticle : public GameObject
{
public:
  SpriteParticle(std::string sprite_name, std::string action, Vector position, AnchorPoint anchor, Vector velocity, Vector acceleration, int drawing_layer = LAYER_OBJECTS-1);
  ~SpriteParticle();
protected:
  virtual void hit(Player& player);
  virtual void update(float elapsed_time);
  virtual void draw(DrawingContext& context);
private:
  Sprite* sprite;
  Vector position;
  Vector velocity;
  Vector acceleration;
  int drawing_layer;
};

#endif
