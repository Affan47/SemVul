static int acurite_tower_decode(r_device* decoder, uint8_t* bb)
{


    int parity = parity_bytes(&bb[2], 4);
    if (parity) {
        decoder_log_bitrow(decoder, 1, __func__, bb, 7 * 8, "bad parity");
        return DECODE_FAIL_MIC;
    }


    char const* channel_str = acurite_getChannel(bb[0]);
    if (*channel_str == 'E') {
        decoder_logf(decoder, 1, __func__, "bad channel Ch %s", channel_str);
        return DECODE_FAIL_SANITY;
    }


    int sensor_id = ((bb[0] & 0x3f) << 8) | bb[1];


    int battery_low = (bb[2] & 0x40) == 0;


    int humidity = (bb[3] & 0x7f);
    if (humidity < 0 || humidity > 100) {
        decoder_logf(decoder, 1, __func__, "0x%04X Ch %s : Impossible humidity: %d %%rH",
                sensor_id, channel_str, humidity);
        return DECODE_FAIL_SANITY;
    }


    int temp_raw = ((bb[4] & 0x7F) << 7) | (bb[5] & 0x7F);
    float tempc = temp_raw * 0.1 - 100;
    if (tempc < -40 || tempc > 70) {
        decoder_logf(decoder, 1, __func__, "0x%04X Ch %s : Impossible temperature: %0.2f C",
                sensor_id, channel_str, tempc);
        return DECODE_FAIL_SANITY;
    }

    data_t* data;

    data = data_make(
            "model",                "",             DATA_STRING, "Acurite-Tower",
            "id",                   "",             DATA_INT,    sensor_id,
            "channel",              NULL,           DATA_STRING, channel_str,
            "battery_ok",           "Battery",      DATA_INT,    !battery_low,
            "temperature_C",        "Temperature",  DATA_FORMAT, "%.1f C", DATA_DOUBLE, tempc,
            "humidity",             "Humidity",     DATA_FORMAT, "%u %%", DATA_INT,    humidity,
            "mic",                  "Integrity",    DATA_STRING, "CHECKSUM",
            NULL);


    decoder_output_data(decoder, data);

    return 1;
}
