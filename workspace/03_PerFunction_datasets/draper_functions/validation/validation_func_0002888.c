Save( MemBuffer &file ) const {
  file.Write8( u_type->ID() );
  file.Write8( u_player ? u_player->ID() : PLAYER_NONE );

  file.Write16( u_pos.x );
  file.Write16( u_pos.y );
  file.Write32( u_flags );
  file.Write16( u_id );

  file.Write8( u_facing );
  file.Write8( u_group );
  file.Write8( u_xp );

  file.Write16( u_target.x );
  file.Write16( u_target.y );
  return 0;
}
