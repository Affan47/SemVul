static void encode_state_run(Encoder *encoder, CommonState *state, unsigned int runlen)
{
    int hits = 0;

    while (runlen >= state->melcorder) {
        hits++;
        runlen -= state->melcorder;
        if (state->melcstate < MELCSTATES - 1) {
            state->melclen = J[++state->melcstate];
            state->melcorder = (1L << state->melclen);
        }
    }


    encode_ones(encoder, hits);

    encode(encoder, runlen, state->melclen + 1);


    if (state->melcstate) {
        state->melclen = J[--state->melcstate];
        state->melcorder = (1L << state->melclen);
    }
}
