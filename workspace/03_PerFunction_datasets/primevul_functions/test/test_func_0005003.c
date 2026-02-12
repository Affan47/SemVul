static int acurite_atlas_decode(r_device *decoder, bitbuffer_t *bitbuffer, unsigned row)
{
    uint8_t humidity, sequence_num, message_type;
    char raw_str[31], *rawp;
    uint16_t sensor_id;
    int raincounter, battery_low;
    int exception = 0;
    float tempf, wind_dir, wind_speed_mph;
    data_t *data;

    int browlen = (bitbuffer->bits_per_row[row] + 7) / 8;
    uint8_t *bb = bitbuffer->bb[row];


    message_type = bb[2] & 0x3f;
    sensor_id = ((bb[0] & 0x03) << 8) | bb[1];
    char const *channel_str = acurite_getChannel(bb[0]);


    rawp = (char *)raw_str;
    for (int i=0; i < MIN(browlen, 15); i++) {
        sprintf(rawp,"%02x",bb[i]);
        rawp += 2;
    }
    *rawp = '\0';


    sequence_num = (bb[0] & 0x0c) >> 2;

    battery_low = (bb[2] & 0x40) == 0;


    wind_speed_mph = ((bb[3] & 0x7F) << 1) | ((bb[4] & 0x40) >> 6);


    data = data_make(
            "model",                "",             DATA_STRING, "Acurite-Atlas",
            "id",                   NULL,           DATA_INT,    sensor_id,
            "channel",              NULL,           DATA_STRING, channel_str,
            "sequence_num",         NULL,           DATA_INT,    sequence_num,
            "battery_ok",           "Battery",      DATA_INT,    !battery_low,
            "message_type",         NULL,           DATA_INT,    message_type,
            "wind_avg_mi_h",        "Wind Speed",   DATA_FORMAT, "%.1f mi/h", DATA_DOUBLE, wind_speed_mph,
            NULL);


    if (message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_TEMP_HUM ||
            message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_TEMP_HUM_LTNG) {


        int temp_raw = (bb[4] & 0x0F) << 7 | (bb[5] & 0x7F);
        tempf = (temp_raw - 400) * 0.1;

        humidity = (bb[6] & 0x7f);


        data = data_append(data,
                "temperature_F",    "temperature",  DATA_FORMAT,    "%.1f F",       DATA_DOUBLE, tempf,
                "humidity",         NULL,           DATA_FORMAT,    "%u %%",        DATA_INT,    humidity,
                NULL);

    }

    if (message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_RAIN ||
            message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_RAIN_LTNG) {

        wind_dir = ((bb[4] & 0x1f) << 5) | ((bb[5] & 0x7c) >> 2);


        raincounter = ((bb[5] & 0x03) << 7) | (bb[6] & 0x7F);


        data = data_append(data,
                "wind_dir_deg",     NULL,           DATA_FORMAT,    "%.1f",         DATA_DOUBLE, wind_dir,
                "rain_in",          "Rainfall Accumulation", DATA_FORMAT, "%.2f in", DATA_DOUBLE, raincounter * 0.01f,
                NULL);

    }

    if (message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_UV_LUX ||
            message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_UV_LUX_LTNG) {

        int uv  = (bb[4] & 0x0f);
        int lux = ((bb[5] & 0x7f) << 7) | (bb[6] & 0x7F);


        data = data_append(data,
                "uv",               NULL,           DATA_INT, uv,
                "lux",              NULL,           DATA_INT, lux * 10,
                NULL);

    }

    if ((message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_TEMP_HUM_LTNG ||
                message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_RAIN_LTNG ||
                message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_UV_LUX_LTNG)) {


        int strike_count    = ((bb[7] & 0x7f) << 2) | ((bb[8] & 0x60) >> 5);
        int strike_distance = bb[8] & 0x1f;


        data = data_append(data,
                "strike_count",         NULL,           DATA_INT, strike_count,
                "strike_distance",      NULL,           DATA_INT, strike_distance,
                NULL);

    }

    data = data_append(data,
            "exception",        "data_exception",   DATA_INT,    exception,
            "raw_msg",          "raw_message",      DATA_STRING, raw_str,
            NULL);

    decoder_output_data(decoder, data);

    return 1;
}
