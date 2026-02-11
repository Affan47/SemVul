make_land(void)
{
  struct terrain *land_fill = NULL;

  if (HAS_POLES) {
    normalize_hmap_poles();
  }


  terrain_type_iterate(pterrain) {
    if (!is_ocean(pterrain)) {
      land_fill = pterrain;
      break;
    }
  } terrain_type_iterate_end;

  fc_assert_exit_msg(NULL != land_fill,
                     "No land terrain type could be found for the purpose "
                     "of temporarily filling in land tiles during map "
                     "generation. This could be an error in Freeciv, or a "
                     "mistake in the terrain.ruleset file. Please make sure "
                     "there is at least one land terrain type in the "
                     "ruleset, or use a different map generator. If this "
                     "error persists, please report it at: %s", BUG_URL);

  hmap_shore_level = (hmap_max_level * (100 - map.server.landpercent)) / 100;
  ini_hmap_low_level();
  whole_map_iterate(ptile) {
    tile_set_terrain(ptile, T_UNKNOWN);
    if (hmap(ptile) < hmap_shore_level) {
      int depth = (hmap_shore_level - hmap(ptile)) * 100 / hmap_shore_level;
      int ocean = 0;
      int land = 0;


      adjc_iterate(ptile, other) {
        if (hmap(other) < hmap_shore_level) {
          ocean++;
        } else {
          land++;
          break;
        }
      } adjc_iterate_end;

      depth += 30 * (ocean - land) / MAX(1, (ocean + land));

      depth = MIN(depth, TERRAIN_OCEAN_DEPTH_MAXIMUM);

      tile_set_terrain(ptile, pick_ocean(depth));
    } else {

      tile_set_terrain(ptile, land_fill);
    }
  } whole_map_iterate_end;

  if (HAS_POLES) {
    renormalize_hmap_poles();
  }


  destroy_tmap();

  create_tmap(TRUE);

  if (HAS_POLES) {
    make_polar_land();
  }

  create_placed_map();
  set_all_ocean_tiles_placed();
  make_relief();
  make_terrains();
  destroy_placed_map();

  make_rivers();
}
