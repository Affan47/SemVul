getProduction() const
{
   if ( productionCache.empty() && !internalUnitProduction.empty() ) {
      for ( int height = 0; height < 8; ++height )
         if ( (1 << height) & baseType->height )
            for ( Production::const_iterator i = internalUnitProduction.begin(); i != internalUnitProduction.end(); ++i )
               if ( baseType->hasFunction( ContainerBaseType::ProduceNonLeavableUnits ) || vehicleUnloadable( *i, height ) )
                  if( find ( productionCache.begin(), productionCache.end(), *i ) == productionCache.end() )
                     productionCache.push_back ( *i );
   }

   return productionCache;
}
