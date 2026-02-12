static void FNAME(update_model)(CommonState *state, s_bucket * const bucket,
                                const BYTE curval)
{
    SPICE_VERIFY(BPC >= 1);
    spice_return_if_fail (bucket != NULL);

    const unsigned int bpp = BPC;
    COUNTER * const pcounters = bucket->pcounters;
    unsigned int i;
    unsigned int bestcode;
    unsigned int bestcodelen;


    bestcode = bpp - 1;
    bestcodelen = (pcounters[bestcode] += FNAME(golomb_code_len)(curval, bestcode));

    for (i = bpp - 2; i < bpp; i--) {
        const unsigned int ithcodelen = (pcounters[i] += FNAME(golomb_code_len)(curval, i));

        if (ithcodelen < bestcodelen) {
            bestcode = i;
            bestcodelen = ithcodelen;
        }
    }

    bucket->bestcode = bestcode;

    if (bestcodelen > state->wm_trigger) {
        for (i = 0; i < bpp; i++) {
            pcounters[i] >>= 1;
        }
    }
}
