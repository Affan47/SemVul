push_isearch (WINDOW *window, int search_index, int direction, int failing)
{
  SEARCH_STATE *state;

  state = xmalloc (sizeof (SEARCH_STATE));
  window_get_state (window, state);
  state->search_index = search_index;
  state->direction = direction;
  state->failing = failing;

  add_pointer_to_array (state, isearch_states_index, isearch_states,
                        isearch_states_slots, 20);
}
