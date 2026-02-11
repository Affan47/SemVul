undoAction( const Context& context )
{
   MapField* fld = getMap()->getField(pos);
   if ( !fld )
      return ActionResult( 21002, pos );

   const BuildingType* buildingType = getMap()->getbuildingtype_byid( buildingTypeID );
   if ( !buildingType )
      return ActionResult( 22500, "Building id is " + ASCString::toString(buildingTypeID));

   if ( !fld->building || fld->building->typ != buildingType )
      return ActionResult( 22502 );

   if ( fld->building->getCompletion() > 0 )
      fld->building->setCompletion( fld->building->getCompletion() -1 );
   else
      delete fld->building;

   return ActionResult(0);
}
