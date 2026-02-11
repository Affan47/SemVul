st_theme_node_paint_state_init (StThemeNodePaintState *state)
{
  int corner_id;

  state->alloc_width = 0;
  state->alloc_height = 0;
  state->node = NULL;
  state->box_shadow_material = COGL_INVALID_HANDLE;
  state->prerendered_texture = COGL_INVALID_HANDLE;
  state->prerendered_material = COGL_INVALID_HANDLE;

  for (corner_id = 0; corner_id < 4; corner_id++)
    state->corner_material[corner_id] = COGL_INVALID_HANDLE;
}
