wav_setup (ao_instance_t * _instance, int sample_rate, int * flags,
                      level_t * level, sample_t * bias)
{
    wav_instance_t * instance = (wav_instance_t *) _instance;

    if ((instance->set_params == 0) && (instance->sample_rate != sample_rate))
        return 1;
    instance->sample_rate = sample_rate;

    if (instance->flags >= 0)
        *flags = instance->flags;
    *level = CONVERT_LEVEL;
    *bias = 0;

    if( instance->flags == DCA_STEREO )
        *bias = CONVERT_BIAS;

    return 0;
}
