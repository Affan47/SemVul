checkbuilding ( Building* b )
{
   if ( b->color/8 == player ) {
      if ((b->netcontrol & (cnet_stopenergyinput << resourcetype)) == 0) {
         int tostore = need-got;

         if ( b->actstorage.resource( resourcetype ) < 0 ) {
            displaymessage("map corruption detected; building %s storage for %d/%d is negative!",1,resourceNames[resourcetype],b->getEntry().x, b->getEntry().y );
            b->actstorage.resource( resourcetype ) = 0;
         }

         if ( b->getStorageCapacity().resource( resourcetype ) - b->actstorage.resource( resourcetype ) < tostore )
            tostore = b->getStorageCapacity().resource( resourcetype ) - b->actstorage.resource( resourcetype );

         if ( !queryonly )
            b->actstorage.resource( resourcetype ) += tostore;
         got += tostore;
      }
   }
}
