setVehicleType( const VehicleType* type )
{
   vehicleTypeID = type->id;

   VehicleType* vt = getMap()->getvehicletype_byid( vehicleTypeID );
   if( !vt )
      throw ActionResult(21701);

   if ( mode != undefined && target.valid())
      setState( SetUp );

}
