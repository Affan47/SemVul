getCommandString() const
{
   ASCString c;
   c.format("constructBuilding ( map, %d, asc.MapCoordinate(%d, %d), %d )", getUnitID(), target.x, target.y, buildingTypeID );
   return c;
}
