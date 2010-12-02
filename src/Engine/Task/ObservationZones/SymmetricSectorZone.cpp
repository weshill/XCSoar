/* Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2010 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
 */
#include "SymmetricSectorZone.hpp"
#include "Task/Tasks/BaseTask/TaskPoint.hpp"

void SymmetricSectorZone::set_legs(const TaskPoint *previous,
                                   const TaskPoint *current,
                                   const TaskPoint *next) 
{
  Angle biSector;
  if (!next && previous) { 
    // final
    biSector = previous->bearing(current->get_location());
  } else if (next && previous) {
    // intermediate
    biSector = previous->bearing(current->get_location()).
      BiSector(current->bearing(next->get_location()));
  } else if (next && !previous) {
    // start
    biSector = next->bearing(current->get_location());
  } else {
    // single point
    biSector = Angle::native(fixed_zero);
  }

  setStartRadial((biSector-SectorAngle*fixed_half).as_bearing());
  setEndRadial((biSector+SectorAngle*fixed_half).as_bearing());
}



bool
SymmetricSectorZone::equals(const ObservationZonePoint* other) const
{
  const SymmetricSectorZone* z = (const SymmetricSectorZone *)other;

  return CylinderZone::equals(other) && SectorAngle == z->getSectorAngle();
}
