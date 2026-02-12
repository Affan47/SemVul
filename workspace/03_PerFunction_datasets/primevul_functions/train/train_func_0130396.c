int detect_frequencies(struct wif *wi)
{
    int start_freq = 2192;
    int end_freq = 2732;
    int max_freq_num = 2048;
    int freq=0, i=0;

    printf("Checking available frequencies, this could take few seconds.\n");

    frequencies = (int*) malloc((max_freq_num+1) * sizeof(int));
    memset(frequencies, 0, (max_freq_num+1) * sizeof(int));
    for(freq=start_freq; freq<=end_freq; freq+=5)
    {
        if(wi_set_freq(wi, freq) == 0)
        {
            frequencies[i] = freq;
            i++;
        }
        if(freq == 2482)
        {

            freq = 2484;
            if(wi_set_freq(wi, freq) == 0)
            {
                frequencies[i] = freq;
                i++;
            }
            freq = 2482;
        }
    }


    start_freq=4800;
    end_freq=6000;
    for(freq=start_freq; freq<=end_freq; freq+=5)
    {
        if(wi_set_freq(wi, freq) == 0)
        {
            frequencies[i] = freq;
            i++;
        }
    }

    printf("Done.\n");
    return 0;
}
