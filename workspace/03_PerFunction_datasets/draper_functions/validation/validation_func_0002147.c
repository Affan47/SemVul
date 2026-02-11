netSetup()
      {
         if ( gamemap && gamemap->network )
            gamemap->network->setup();
         return true;
      }
