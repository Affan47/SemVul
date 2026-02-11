externallyAvailable()
{
   Vehicle* srcVehicle = dynamic_cast<Vehicle*>(source);
   if ( srcVehicle ) {
      if ( srcVehicle->attacked )
         return false;


      if ( srcVehicle->reactionfire.getStatus() == Vehicle::ReactionFire::off || srcVehicle->baseType->hasFunction(ContainerBaseType::MoveWithReactionFire))
         if ( source->getMap()->getField( source->getPosition() )->unitHere( srcVehicle )) {
            const SingleWeapon* weap = getServiceWeapon();
            if( weap )
               if ( source->baseType->hasFunction( ContainerBaseType::ExternalEnergyTransfer  ) ||
                    source->baseType->hasFunction( ContainerBaseType::ExternalMaterialTransfer  ) ||
                    source->baseType->hasFunction( ContainerBaseType::ExternalFuelTransfer  ) ||
                    source->baseType->hasFunction( ContainerBaseType::ExternalAmmoTransfer  ))
                    return true;

         }
   } else {
      if ( source->baseType->hasFunction( ContainerBaseType::ExternalEnergyTransfer  ) )

            return true;

      if ( source->baseType->hasFunction( ContainerBaseType::ExternalMaterialTransfer  ) )

            return true;

      if ( source->baseType->hasFunction( ContainerBaseType::ExternalFuelTransfer  ) )

            return true;

   }
   return false;
}
