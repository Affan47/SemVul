spawnNextItem( PG_Widget* parent, const PG_Point& pos )
   {
      if ( it != items.end() ) {
         const Technology* v = *(it++);

         return new TechWidget( parent, pos, parent->Width() - 15, v, player.getPosition() );
      } else
         return NULL;
   }
