HT_destroy( HashTable table, HTDestroyFunc destroy )
{
  DEBUG( MAIN, ("HT_destroy( %p )\n", table) );

  if( table == NULL )
    return;

  AssertValidPtr( table );
  AssertValidPtr( table->root );

  CHANGE_STATE(table);

  HT_flush( table, destroy );

  Free( table->root );
  Free( table );

  DEBUG( MAIN, ("destroyed hash table @ %p\n", table) );
}
