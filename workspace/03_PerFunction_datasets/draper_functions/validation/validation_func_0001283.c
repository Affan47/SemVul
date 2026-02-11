setMaxValue
      (
         SemaphoreGroupPtr aGroup,
         Int               aId,
         Int               aValue
      )
   {
      REQUIRE( aGroup != NULLPTR );
      Int   results(0);

      if( aGroup->isPrivate() == true )
      {
         semctl( (Int)aGroup->theIdentifier, aId, SETVAL, aValue );
      }
      else
      {
         ;
      }

      return results;
   }
