decode(ima_adpcm_state_t *s, uint8_t adpcm)
{
    int e;
    int ss;
    int16_t linear;


    ss = step_size[s->step_index];
    e = ss >> 3;
    if (adpcm & 0x01)
        e += (ss >> 2);

    if (adpcm & 0x02)
        e += (ss >> 1);

    if (adpcm & 0x04)
        e += ss;

    if (adpcm & 0x08)
        e = -e;

    linear = saturate(s->last + e);
    s->last = linear;
    s->step_index += step_adjustment[adpcm & 0x07];
    if (s->step_index < 0)
        s->step_index = 0;
    else if (s->step_index > STEP_MAX)
        s->step_index = STEP_MAX;

    return linear;
}
