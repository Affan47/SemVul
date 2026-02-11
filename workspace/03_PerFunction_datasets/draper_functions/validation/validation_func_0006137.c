vmdaudio_decode_audio(VmdAudioContext *s, unsigned char *data,
    const uint8_t *buf, int buf_size, int stereo)
{
    int i;
    int chan = 0;
    int16_t *out = (int16_t*)data;

    for(i = 0; i < buf_size; i++) {
        if(buf[i] & 0x80)
            s->predictors[chan] -= vmdaudio_table[buf[i] & 0x7F];
        else
            s->predictors[chan] += vmdaudio_table[buf[i]];
        s->predictors[chan] = av_clip_int16(s->predictors[chan]);
        out[i] = s->predictors[chan];
        chan ^= stereo;
    }
}
