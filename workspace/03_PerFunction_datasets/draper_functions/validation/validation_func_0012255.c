unload_level (void)
{
  dmsg (D_LEVEL, "unloading level");

  uninit_render_data ();
  uninit_bonuses_level ();
  img_free (&tile_set_img);
  free (square_occupied);
  release_explosions ();
  free (square_way);
  free (square_tile);
  free (square_coord);
  if (game_mode == M_KILLEM && !in_menu) {
    free (square_lemmings_list);
    free (square_dead_lemmings_list);
  }
  if (game_mode >= M_TCASH && !in_menu)
    free (square_object);
  lvl_free (&lvl);
  unload_soundtrack ();
}
