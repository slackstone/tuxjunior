//  $Id: path.hpp 5064 2007-05-27 21:51:46Z sommer $
//
//  SuperTux Path
//  Copyright (C) 2005 Philipp <balinor@pnxs.de>
//  Copyright (C) 2006 Christoph Sommer <christoph.sommer@2006.expires.deltadevelopment.de>
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.
#ifndef __PATH_HPP__
#define __PATH_HPP__

#include <vector>
#include "math/vector.hpp"
#include "lisp/lisp.hpp"
#include "serializable.hpp"

class Path : public Serializable
{
public:
  Path();
  ~Path();

  void read(const lisp::Lisp& reader);
  void write(lisp::Writer& writer);

  Vector get_base() const;

  /**
   * Helper class that stores an individual node of a Path
   */
  class Node
  {
  public:
    Vector position; /**< the position of this node */
    float time; /**< time (in seconds) to get from this node to next node */
  };

  std::vector<Node> nodes;

  /**
   * returns Node index nearest to reference_point or -1 if not applicable
   */
  int get_nearest_node_no(Vector reference_point) const;

  /**
   * returns Node index farthest from reference_point or -1 if not applicable
   */
  int get_farthest_node_no(Vector reference_point) const;

private:
  friend class PathWalker;

  enum WalkMode {
    // moves from first to last path node and stops
    ONE_SHOT,
    // moves from first to last node then in reverse order back to first
    PING_PONG,
    // moves from last node back to the first node
    CIRCULAR
  };

  WalkMode mode;
};

#endif
