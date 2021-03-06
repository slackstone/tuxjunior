//  $Id: totem.cpp 4435 2006-11-04 14:13:27Z sommer $
//
//  SuperTux - "Totem" Badguy
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.

#include <config.h>

#include "totem.hpp"
#include "log.hpp"

static const float WALKSPEED = 100;
static const float JUMP_ON_SPEED_Y = -400;
static const float JUMP_OFF_SPEED_Y = -500;
static const std::string LAND_ON_TOTEM_SOUND = "sounds/totem.ogg";

Totem::Totem(const lisp::Lisp& reader)
	: BadGuy(reader, "images/creatures/totem/totem.sprite")
{
  carrying = 0;
  carried_by = 0;
  sound_manager->preload( LAND_ON_TOTEM_SOUND );
}

Totem::Totem(const Totem& other)
	: BadGuy(other), carrying(other.carrying), carried_by(other.carried_by)
{
  sound_manager->preload( LAND_ON_TOTEM_SOUND );
}

Totem::~Totem()
{
  if (carrying) carrying->jump_off();
  if (carried_by) jump_off();
}

bool
Totem::updatePointers(const GameObject* from_object, GameObject* to_object)
{
  if (from_object == carrying) {
    carrying = dynamic_cast<Totem*>(to_object);
    return true;
  }
  if (from_object == carried_by) {
    carried_by = dynamic_cast<Totem*>(to_object);
    return true;
  }
  return false;
}

void
Totem::write(lisp::Writer& writer)
{
  writer.start_list("totem");

  writer.write_float("x", start_position.x);
  writer.write_float("y", start_position.y);

  writer.end_list("totem");
}

void
Totem::activate()
{
  if (!carried_by) {
    physic.set_velocity_x(dir == LEFT ? -WALKSPEED : WALKSPEED);
    sprite->set_action(dir == LEFT ? "walking-left" : "walking-right");
    return;
  } else {
    synchronize_with(carried_by);
    sprite->set_action(dir == LEFT ? "stacked-left" : "stacked-right");
    return;
  }
}

void
Totem::active_update(float elapsed_time)
{
  BadGuy::active_update(elapsed_time);

  if (!carried_by) {
    if (on_ground() && might_fall())
    {
      dir = (dir == LEFT ? RIGHT : LEFT);
      activate();
    }

    Sector* s = Sector::current();
    if (s) {
      // jump a bit if we find a suitable totem
      for (std::vector<MovingObject*>::iterator i = s->moving_objects.begin(); i != s->moving_objects.end(); i++) {
	Totem* t = dynamic_cast<Totem*>(*i);
	if (!t) continue;

	// skip if we are not approaching each other
	if (!((this->dir == LEFT) && (t->dir == RIGHT))) continue;

	Vector p1 = this->get_pos();
	Vector p2 = t->get_pos();

	// skip if not on same height
	float dy = (p1.y - p2.y);
	if (fabsf(dy - 0) > 2) continue;

	// skip if too far away
	float dx = (p1.x - p2.x);
	if (fabsf(dx - 128) > 2) continue;

	physic.set_velocity_y(JUMP_ON_SPEED_Y);
	p1.y -= 1;
	this->set_pos(p1);
	break;
      }
    }
  }

  if (carried_by) {
    this->synchronize_with(carried_by);
  }

  if (carrying) {
    carrying->synchronize_with(this);
  }

}

bool
Totem::collision_squished(GameObject& object)
{
  if (carrying) carrying->jump_off();
  if (carried_by) {
    Player* player = dynamic_cast<Player*>(&object);
    if (player) player->bounce(*this);
    jump_off();
  }

  sprite->set_action(dir == LEFT ? "squished-left" : "squished-right");
  bbox.set_size(sprite->get_current_hitbox_width(), sprite->get_current_hitbox_height());

  kill_squished(object);
  return true;
}

void
Totem::collision_solid(const CollisionHit& hit)
{
  update_on_ground_flag(hit);

  // if we are being carried around, pass event to bottom of stack and ignore it
  if (carried_by) {
    carried_by->collision_solid(hit);
    return;
  }

  // If we hit something from above or below: stop moving in this direction
  if (hit.top || hit.bottom) {
    physic.set_velocity_y(0);
  }

  // If we are hit from the direction we are facing: turn around
  if (hit.left && (dir == LEFT)) {
    dir = RIGHT;
    activate();
  }
  if (hit.right && (dir == RIGHT)) {
    dir = LEFT;
    activate();
  }
}

HitResponse
Totem::collision_badguy(BadGuy& badguy, const CollisionHit& hit)
{
  // if we are being carried around, pass event to bottom of stack and ignore it
  if (carried_by) {
    carried_by->collision_badguy(badguy, hit);
    return CONTINUE;
  }

  // if we hit a Totem that is not from our stack: have our base jump on its top
  Totem* totem = dynamic_cast<Totem*>(&badguy);
  if (totem) {
    Totem* thisBase = this; while (thisBase->carried_by) thisBase=thisBase->carried_by;
    Totem* srcBase = totem; while (srcBase->carried_by)  srcBase=srcBase->carried_by;
    Totem* thisTop = this;  while (thisTop->carrying)    thisTop=thisTop->carrying;
    if (srcBase != thisBase) {
      srcBase->jump_on(thisTop);
    }
  }

  // If we are hit from the direction we are facing: turn around
  if(hit.left && (dir == LEFT)) {
    dir = RIGHT;
    activate();
  }
  if(hit.right && (dir == RIGHT)) {
    dir = LEFT;
    activate();
  }

  return CONTINUE;
}

void
Totem::kill_fall()
{
  if (carrying) carrying->jump_off();
  if (carried_by) jump_off();

  BadGuy::kill_fall();
}

void
Totem::jump_on(Totem* target)
{
  if (target->carrying) {
    log_warning << "target is already carrying someone" << std::endl;
    return;
  }

  target->carrying = this;

  this->carried_by = target;
  this->activate();
  bbox.set_size(sprite->get_current_hitbox_width(), sprite->get_current_hitbox_height());

  sound_manager->play( LAND_ON_TOTEM_SOUND , get_pos());


  this->synchronize_with(target);
}

void
Totem::jump_off() {
  if (!carried_by) {
    log_warning << "not carried by anyone" << std::endl;
    return;
  }

  carried_by->carrying = 0;

  this->carried_by = 0;

  this->activate();
  bbox.set_size(sprite->get_current_hitbox_width(), sprite->get_current_hitbox_height());


  physic.set_velocity_y(JUMP_OFF_SPEED_Y);
}

void
Totem::synchronize_with(Totem* base)
{

  if (dir != base->dir) {
    dir = base->dir;
    sprite->set_action(dir == LEFT ? "stacked-left" : "stacked-right");
  }

  Vector pos = base->get_pos();
  pos.y -= sprite->get_current_hitbox_height();
  set_pos(pos);

  physic.set_velocity_x(base->physic.get_velocity_x());
  physic.set_velocity_y(base->physic.get_velocity_y());
}


IMPLEMENT_FACTORY(Totem, "totem")
