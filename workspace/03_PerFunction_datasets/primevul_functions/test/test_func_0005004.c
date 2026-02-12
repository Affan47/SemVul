static int acurite_leak_detector_decode(r_device* decoder, uint8_t* bb)
{


    int parity = parity_bytes(&bb[2], 4);
    if (parity) {
        decoder_log_bitrow(decoder, 1, __func__, bb, 7 * 8, "bad parity");
        return DECODE_FAIL_MIC;
    }


    char const* channel_str = acurite_getChannel(bb[0]);
    if (*channel_str == 'E') {
        decoder_logf(decoder, 1, __func__, "Acurite TXR sensor : bad channel Ch %s", channel_str);
        return DECODE_FAIL_SANITY;
    }


    int sensor_id = ((bb[0] & 0x3f) << 8) | bb[1];


    int battery_low = (bb[2] & 0x40) == 0;


    int is_wet = (bb[3] & 0x10) >> 4;

    data_t* data;

    data = data_make(
            "model",                "",             DATA_STRING, "Acurite-Leak",
            "id",                   "",             DATA_INT,    sensor_id,
            "channel",              NULL,           DATA_STRING, channel_str,
            "battery_ok",           "Battery",      DATA_INT,    !battery_low,
            "leak_detected",        "Leak",         DATA_INT,    is_wet,
            "mic",                  "Integrity",    DATA_STRING, "CHECKSUM",
            NULL);


    decoder_output_data(decoder, data);

    return 1;
}
