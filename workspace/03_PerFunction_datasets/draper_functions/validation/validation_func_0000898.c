t38_encode_indicator(t38_core_state_t *s, uint8_t buf[], int indicator)
{
    int len;


    if (indicator <= T38_IND_V17_14400_LONG_TRAINING)
    {
        buf[0] = (uint8_t) (indicator << 1);
        len = 1;
    }
    else if (s->t38_version != 0  &&  indicator <= T38_IND_V33_14400_TRAINING)
    {
        buf[0] = (uint8_t) (0x20 | (((indicator - T38_IND_V8_ANSAM) & 0xF) >> 2));
        buf[1] = (uint8_t) (((indicator - T38_IND_V8_ANSAM) << 6) & 0xFF);
        len = 2;
    }
    else
    {
        len = -1;
    }
    return len;
}
