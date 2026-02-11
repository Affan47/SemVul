putResource ( int      need,    int resourcetype, bool queryonly, int scope, int player  )
{
   if ( need < 0 )
      return -getResource( -need, resourcetype, queryonly, scope, player );
   else {
      int placed;
      {
         PutResource putresource ( getMap(), scope );
         placed = putresource.getresource ( entryPosition.x, entryPosition.y, resourcetype, need, queryonly, player >= 0 ? player : getMap()->actplayer, scope );
      }


      return placed;
   }
}
