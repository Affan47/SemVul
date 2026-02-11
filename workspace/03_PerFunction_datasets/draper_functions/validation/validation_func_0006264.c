s_Bicubic_data_at(stream_Bicubic_state *const ss, int x, int y, int c)
{
    ulong idx;
    if (y >= ss->HeightIn)
        y = ss->HeightIn - 1;
    y -= ss->y_in;
    idx = ss->l_size * (y < 0 ? 0 : y) +
        (x < 0 ? 0 : x >= ss->WidthIn ? ss->WidthIn-1 : x) * ss->Colors + c;
    return (idx < ss->d_len) ? ss->data[idx] : 0;
}
