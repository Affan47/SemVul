static int acurite_txr_decode(r_device *decoder, bitbuffer_t *bitbuffer)
{
    int browlen, valid = 0;
    uint8_t *bb;
    float tempf, wind_dir, wind_speed_kph, wind_speed_mph;
    uint8_t humidity, sequence_num, message_type;

    uint16_t sensor_id;
    int raincounter, battery_low;
    data_t *data;

    bitbuffer_invert(bitbuffer);

    for (uint16_t brow = 0; brow < bitbuffer->num_rows; ++brow) {
        browlen = (bitbuffer->bits_per_row[brow] + 7)/8;
        bb = bitbuffer->bb[brow];

        decoder_logf(decoder, 2, __func__, "row %u bits %u, bytes %d", brow, bitbuffer->bits_per_row[brow], browlen);

        if ((bitbuffer->bits_per_row[brow] < ACURITE_TXR_BITLEN ||
                bitbuffer->bits_per_row[brow] > ACURITE_5N1_BITLEN + 1)
                && bitbuffer->bits_per_row[brow] != ACURITE_6045_BITLEN
                && bitbuffer->bits_per_row[brow] != ACURITE_ATLAS_BITLEN
                && bitbuffer->bits_per_row[brow] != ACURITE_515_BITLEN) {
            if (bitbuffer->bits_per_row[brow] > 16)
                decoder_log(decoder, 2, __func__, "skipping wrong len");
            continue;
        }


        if (bb[browlen - 1] == 0)
            browlen--;


        int sum = add_bytes(bb, browlen - 1);
        if (sum == 0 || (sum & 0xff) != bb[browlen - 1]) {
            decoder_log_bitrow(decoder, 1, __func__, bb, bitbuffer->bits_per_row[brow], "bad checksum");
            continue;
        }


        message_type = bb[2] & 0x3f;


        if (browlen == ACURITE_TXR_BITLEN / 8) {
            int decoded = 0;

            if (message_type == ACURITE_MSGTYPE_LEAK_DETECTOR) {
                decoded = acurite_leak_detector_decode(decoder, bb);
            } else if (message_type == ACURITE_MSGTYPE_TOWER_SENSOR) {
                decoded = acurite_tower_decode(decoder, bb);
            }


            if (decoded > 0) {
                valid++;
            }
        }


        if (browlen == ACURITE_515_BITLEN / 8) {
            char const *channel_str = acurite_getChannelAndType(bb[0], message_type);


            sensor_id = ((bb[0] & 0x3f) << 8) | bb[1];


            if (message_type != ACURITE_MSGTYPE_515_REFRIGERATOR
                    && message_type != ACURITE_MSGTYPE_515_FREEZER) {
                decoder_logf(decoder, 2, __func__, "Acurite 515 sensor 0x%04X Ch %s, Unknown message type 0x%02x",
                        sensor_id, channel_str, message_type);
                continue;
            }


            int temp_raw = ((bb[3] & 0x7F) << 7) | (bb[4] & 0x7F);
            tempf = (temp_raw - 1480) * 0.1f;

            battery_low = (bb[2] & 0x40) == 0;


            data = data_make(
                    "model",                "",             DATA_STRING, "Acurite-515",
                    "id",                   "",             DATA_INT,    sensor_id,
                    "channel",              NULL,           DATA_STRING, channel_str,
                    "battery_ok",           "Battery",      DATA_INT,    !battery_low,
                    "temperature_F",        "Temperature",  DATA_FORMAT, "%.1f F", DATA_DOUBLE, tempf,
                    "mic",                  "Integrity",    DATA_STRING, "CHECKSUM",
                    NULL);


            decoder_output_data(decoder, data);
            valid++;
        }


        else if (message_type == ACURITE_MSGTYPE_5N1_WINDSPEED_WINDDIR_RAINFALL ||
                 message_type == ACURITE_MSGTYPE_5N1_WINDSPEED_TEMP_HUMIDITY ||
                 message_type == ACURITE_MSGTYPE_3N1_WINDSPEED_TEMP_HUMIDITY ||
                 message_type == ACURITE_MSGTYPE_RAINFALL) {
            decoder_log_bitrow(decoder, 1, __func__, bb, bitbuffer->bits_per_row[brow], "Acurite 5n1 raw msg");
            char const *channel_str = acurite_getChannel(bb[0]);


            sensor_id    = ((bb[0] & 0x0f) << 8) | bb[1];


            sequence_num = (bb[0] & 0x30) >> 4;
            battery_low = (bb[2] & 0x40) == 0;


            int speed_raw = ((bb[3] & 0x1F) << 3)| ((bb[4] & 0x70) >> 4);
            wind_speed_kph = 0;
            if (speed_raw > 0) {
                wind_speed_kph = speed_raw * 0.8278 + 1.0;
            }

            if (message_type == ACURITE_MSGTYPE_5N1_WINDSPEED_WINDDIR_RAINFALL) {

                wind_dir = acurite_5n1_winddirections[bb[4] & 0x0f] * 22.5f;


                raincounter = ((bb[5] & 0x7f) << 7) | (bb[6] & 0x7F);


                data = data_make(
                        "model",        "",   DATA_STRING,    "Acurite-5n1",
                        "message_type", NULL,   DATA_INT,       message_type,
                        "id",           NULL, DATA_INT,       sensor_id,
                        "channel",      NULL,   DATA_STRING,    channel_str,
                        "sequence_num",  NULL,   DATA_INT,      sequence_num,
                        "battery_ok",       "Battery",      DATA_INT,    !battery_low,
                        "wind_avg_km_h",   "wind_speed",   DATA_FORMAT,    "%.1f km/h", DATA_DOUBLE,     wind_speed_kph,
                        "wind_dir_deg", NULL,   DATA_FORMAT,    "%.1f", DATA_DOUBLE,    wind_dir,
                        "rain_in",      "Rainfall Accumulation",   DATA_FORMAT, "%.2f in", DATA_DOUBLE, raincounter * 0.01f,
                        "mic",                  "Integrity",    DATA_STRING, "CHECKSUM",
                        NULL);


                decoder_output_data(decoder, data);
                valid++;
            }
            else if (message_type == ACURITE_MSGTYPE_5N1_WINDSPEED_TEMP_HUMIDITY) {


                int temp_raw = (bb[4] & 0x0F) << 7 | (bb[5] & 0x7F);
                tempf = (temp_raw - 400) * 0.1f;

                humidity = (bb[6] & 0x7f);


                data = data_make(
                        "model",        "",   DATA_STRING,    "Acurite-5n1",
                        "message_type", NULL,   DATA_INT,       message_type,
                        "id",           NULL, DATA_INT,  sensor_id,
                        "channel",      NULL,   DATA_STRING,    channel_str,
                        "sequence_num",  NULL,   DATA_INT,      sequence_num,
                        "battery_ok",       "Battery",      DATA_INT,    !battery_low,
                        "wind_avg_km_h",   "wind_speed",   DATA_FORMAT,    "%.1f km/h", DATA_DOUBLE,     wind_speed_kph,
                        "temperature_F",     "temperature",    DATA_FORMAT,    "%.1f F", DATA_DOUBLE,    tempf,
                        "humidity",     NULL,    DATA_FORMAT,    "%u %%",   DATA_INT,   humidity,
                        "mic",                  "Integrity",    DATA_STRING, "CHECKSUM",
                        NULL);


                decoder_output_data(decoder, data);
                valid++;
            }
            else if (message_type == ACURITE_MSGTYPE_3N1_WINDSPEED_TEMP_HUMIDITY) {

                sensor_id = ((bb[0] & 0x3f) << 8) | bb[1];
                humidity = (bb[3] & 0x7f);


                int temp_raw = (bb[4] & 0x1F) << 7 | (bb[5] & 0x7F);
                tempf        = (temp_raw - 1480) * 0.1f;

                wind_speed_mph = bb[6] & 0x7f;


                data = data_make(
                        "model",        "",   DATA_STRING,    "Acurite-3n1",
                        "message_type", NULL,   DATA_INT,       message_type,
                        "id",    NULL,   DATA_FORMAT,    "0x%02X",   DATA_INT,       sensor_id,
                        "channel",      NULL,   DATA_STRING,    channel_str,
                        "sequence_num",  NULL,   DATA_INT,      sequence_num,
                        "battery_ok",       "Battery",      DATA_INT,    !battery_low,
                        "wind_avg_mi_h",   "wind_speed",   DATA_FORMAT,    "%.1f mi/h", DATA_DOUBLE,     wind_speed_mph,
                        "temperature_F",     "temperature",    DATA_FORMAT,    "%.1f F", DATA_DOUBLE,    tempf,
                        "humidity",     NULL,    DATA_FORMAT,    "%u %%",   DATA_INT,   humidity,
                        "mic",                  "Integrity",    DATA_STRING, "CHECKSUM",
                        NULL);


                decoder_output_data(decoder, data);
                valid++;
            }
            else if (message_type == ACURITE_MSGTYPE_RAINFALL) {


                int channel = bb[0] >> 6;
                raincounter = ((bb[5] & 0x7f) << 7) | (bb[6] & 0x7f);


                data = data_make(
                        "model",            "",                         DATA_STRING, "Acurite-Rain899",
                        "id",               "",                         DATA_INT,    sensor_id,
                        "channel",          "",                         DATA_INT,    channel,
                        "battery_ok",       "Battery",                  DATA_INT,    !battery_low,
                        "rain_mm",          "Rainfall Accumulation",    DATA_FORMAT, "%.2f mm", DATA_DOUBLE, raincounter * 0.254,
                        "mic",                  "Integrity",    DATA_STRING, "CHECKSUM",
                        NULL);


                decoder_output_data(decoder, data);
                valid++;
            }
            else {
                decoder_logf(decoder, 2, __func__, "Acurite 5n1 sensor 0x%04X Ch %s, Status %02X, Unknown message type 0x%02x",
                        sensor_id, channel_str, bb[3], message_type);
            }
        }

        else if (message_type == ACURITE_MSGTYPE_6045M) {

            valid += acurite_6045_decode(decoder, bitbuffer, brow);
        }

        else if ((message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_TEMP_HUM ||
                  message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_RAIN ||
                  message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_UV_LUX ||
                  message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_TEMP_HUM_LTNG ||
                  message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_RAIN_LTNG ||
                  message_type == ACURITE_MSGTYPE_ATLAS_WNDSPD_UV_LUX_LTNG)) {
            valid += acurite_atlas_decode(decoder, bitbuffer, brow);
        }
    }

    return valid;
}
