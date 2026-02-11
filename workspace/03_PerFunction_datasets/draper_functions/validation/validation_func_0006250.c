RegisterBattle( Unit *att, Unit *def ) {
  battles.AddTail( new Combat( att, def ) );
  att->Attack( def );
  if ( history ) history->RecordAttackEvent( *att, *def );
}
