audio_amplify (float * data, int channels, int frames, float * factors)
{
    float * end = data + channels * frames;
    int channel;

    while (data < end)
    {
        for (channel = 0; channel < channels; channel ++)
        {
            * data = * data * factors[channel];
            data ++;
        }
    }
}
