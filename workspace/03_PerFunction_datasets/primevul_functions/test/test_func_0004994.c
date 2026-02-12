static int acurite_6045_decode(r_device *decoder, bitbuffer_t *bitbuffer, unsigned row)
{
    float tempf;
    uint8_t humidity;

    char raw_str[31], *rawp;
    uint16_t sensor_id;
    uint8_t strike_count, strike_distance;
    int battery_low, active, rfi_detect;
    int exception = 0;
    data_t *data;

    int browlen = (bitbuffer->bits_per_row[row] + 7) / 8;
    uint8_t *bb = bitbuffer->bb[row];

    char const *channel_str = acurite_getChannel(bb[0]);


    sensor_id = ((bb[0] & 0x3f) << 8) | bb[1];
    battery_low = (bb[2] & 0x40) == 0;
    humidity = (bb[3] & 0x7f);
    active = (bb[4] & 0x40) == 0x40;


    int temp_raw = ((bb[4] & 0x1F) << 7) | (bb[5] & 0x7F);
    tempf = (temp_raw - 1480) * 0.1f;


    strike_count = ((bb[6] & 0x7f) << 1) | ((bb[7] & 0x40) >> 6);
    strike_distance = bb[7] & 0x1f;
    rfi_detect = (bb[7] & 0x20) == 0x20;


    rawp = (char *)raw_str;
    for (int i=0; i < MIN(browlen, 15); i++) {
        sprintf(rawp,"%02x",bb[i]);
        rawp += 2;
    }
    *rawp = '\0';


    if (((bb[4] & 0x20) != 0) ||
        (humidity > 100) ||
        (tempf > 158) ||
        (tempf < -40)) {
        exception++;
    }


    data = data_make(
            "model",            "",                 DATA_STRING, "Acurite-6045M",
            "id",               NULL,               DATA_INT,    sensor_id,
            "channel",          NULL,               DATA_STRING, channel_str,
            "battery_ok",       "Battery",          DATA_INT,    !battery_low,
            "temperature_F",    "temperature",      DATA_FORMAT, "%.1f F",     DATA_DOUBLE,     tempf,
            "humidity",         "humidity",         DATA_FORMAT, "%u %%", DATA_INT,    humidity,
            "strike_count",     "strike_count",     DATA_INT,    strike_count,
            "storm_dist",       "storm_distance",   DATA_INT,    strike_distance,
            "active",           "active_mode",      DATA_INT,    active,
            "rfi",              "rfi_detect",       DATA_INT,    rfi_detect,
            "exception",        "data_exception",   DATA_INT,    exception,
            "raw_msg",          "raw_message",      DATA_STRING, raw_str,
            NULL);


    decoder_output_data(decoder, data);
    return 1;
}
