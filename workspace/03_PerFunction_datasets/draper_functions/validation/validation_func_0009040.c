createSemaphore( void )
                           throw( SemaphoreException )
   {
      AbstractSemaphorePtr aSem(NULLPTR);
      Short maxSems( getSemaphoreCount() );

      for( Short x = 0; x < maxSems && aSem == NULLPTR ; ++x )
      {
         if( theUsedMap[x] == NULLPTR )
         {
            SemaphoreIdentifier  aSemId(x);
            theUsedMap[x] = aSem =
               new GuardSemaphore
                  (
                     this,
                     aSemId
                  );
         }
         else
         {
            ;
         }
      }

      if( aSem == NULLPTR )
      {
         throw SemaphoreException
            (
               "Can't create semaphore",
               LOCATION,
               Exception::CONTINUABLE
            );
      }

      return aSem;
   }
