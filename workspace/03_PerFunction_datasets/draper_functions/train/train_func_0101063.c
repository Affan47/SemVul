filter_channel(MLPDecodeContext *m, unsigned int substr,
                           unsigned int channel)
{
    SubStream *s = &m->substream[substr];
    int32_t filter_state_buffer[NUM_FILTERS][MAX_BLOCKSIZE + MAX_FILTER_ORDER];
    FilterParams *fp[NUM_FILTERS] = { &m->channel_params[channel].filter_params[FIR],
                                      &m->channel_params[channel].filter_params[IIR], };
    unsigned int filter_shift = fp[FIR]->shift;
    int32_t mask = MSB_MASK(s->quant_step_size[channel]);
    int index = MAX_BLOCKSIZE;
    int j, i;

    for (j = 0; j < NUM_FILTERS; j++) {
        memcpy(&filter_state_buffer[j][MAX_BLOCKSIZE], &fp[j]->state[0],
               MAX_FILTER_ORDER * sizeof(int32_t));
    }

    for (i = 0; i < s->blocksize; i++) {
        int32_t residual = m->sample_buffer[i + s->blockpos][channel];
        unsigned int order;
        int64_t accum = 0;
        int32_t result;


        for (j = 0; j < NUM_FILTERS; j++)
            for (order = 0; order < fp[j]->order; order++)
                accum += (int64_t)filter_state_buffer[j][index + order] *
                                  fp[j]->coeff[order];

        accum  = accum >> filter_shift;
        result = (accum + residual) & mask;

        --index;

        filter_state_buffer[FIR][index] = result;
        filter_state_buffer[IIR][index] = result - accum;

        m->sample_buffer[i + s->blockpos][channel] = result;
    }

    for (j = 0; j < NUM_FILTERS; j++) {
        memcpy(&fp[j]->state[0], &filter_state_buffer[j][index],
               MAX_FILTER_ORDER * sizeof(int32_t));
    }
}
