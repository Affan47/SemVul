static inline uint8_t ide_atapi_set_profile(uint8_t *buf, uint8_t *index,
                                            uint16_t profile)
{
    uint8_t *buf_profile = buf + 12;

    buf_profile += ((*index) * 4);
    stw_be_p(buf_profile, profile);
    buf_profile[2] = ((buf_profile[0] == buf[6]) && (buf_profile[1] == buf[7]));


    (*index)++;
    buf[11] += 4;

    return 4;
}
