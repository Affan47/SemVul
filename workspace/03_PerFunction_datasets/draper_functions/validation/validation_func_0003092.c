write_frame_list (void * key, void * list, void * user)
{
    WriteState * state = user;

    for (GList * node = list; node; node = node->next)
    {
        int size;
        if (write_frame (state->file, node->data, & size))
            state->written_size += size;
    }
}
