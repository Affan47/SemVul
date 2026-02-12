static void annotate_state_start(annotate_state_t *state)
{

    construct_hash_table(&state->entry_table, 100, 1);
    construct_hash_table(&state->server_table, 10, 1);
}
