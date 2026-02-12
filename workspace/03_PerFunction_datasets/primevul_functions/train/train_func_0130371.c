int rearrange_frequencies()
{
    int *freqs;
    int count, left, pos;
    int width, last_used=0;
    int cur_freq, last_freq, round_done;


    width = DEFAULT_CWIDTH;
    cur_freq=0;

    count = getfreqcount(0);
    left = count;
    pos = 0;

    freqs = malloc(sizeof(int) * (count + 1));
    memset(freqs, 0, sizeof(int) * (count + 1));
    round_done = 0;

    while(left > 0)
    {

        last_freq = cur_freq;
        cur_freq = G.own_frequencies[pos%count];
        if(cur_freq == last_used)
            round_done=1;

        if(((count-left) > 0) && !round_done && ( ABS( last_used-cur_freq ) < width ) )
        {

            pos++;
            continue;
        }
        if(!array_contains( freqs, count, cur_freq))
        {

            freqs[count - left] = cur_freq;
            last_used = cur_freq;
            left--;
            round_done = 0;
        }

        pos++;
    }

    memcpy(G.own_frequencies, freqs, count*sizeof(int));
    free(freqs);

    return 0;
}
