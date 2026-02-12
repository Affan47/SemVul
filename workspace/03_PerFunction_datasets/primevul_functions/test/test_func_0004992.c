static int acurite_590tx_decode(r_device *decoder, bitbuffer_t *bitbuffer)
{
    data_t *data;
    uint8_t *b;
    int row;
    int sensor_id;
    int battery_ok;
    int channel;
    int humidity;
    int temp_raw;
    float temp_c;

    row = bitbuffer_find_repeated_row(bitbuffer, 3, 25);
    if (row < 0)
        return DECODE_ABORT_EARLY;

    if (bitbuffer->bits_per_row[row] > 25)
        return DECODE_ABORT_LENGTH;

    b = bitbuffer->bb[row];

    if (b[4] != 0)
        return DECODE_FAIL_SANITY;


    if (b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 0)
        return DECODE_FAIL_SANITY;


    uint8_t parity = b[0];
    parity = (parity >> 4) ^ (parity & 0xF);
    parity = (parity >> 2) ^ (parity & 0x3);
    parity ^= b[1] >> 6;
    parity = (parity >> 1) ^ (parity & 0x1);

    if (!parity) {
        decoder_log(decoder, 1, __func__, "parity check failed");
        return DECODE_FAIL_MIC;
    }


    sensor_id = b[0] & 0xFE;
    battery_ok = (b[0] & 0x01);


    channel = (b[1] >> 4) & 0x03;

    temp_raw = (int16_t)(((b[1] & 0x0F) << 12) | (b[2] << 4));
    temp_raw = temp_raw >> 4;
    temp_c   = (temp_raw - 500) * 0.1f;

    if (temp_raw >= 0 && temp_raw <= 100)
        humidity = temp_raw;
    else
        humidity = -1;


     data = data_make(
            "model",            "",             DATA_STRING, "Acurite-590TX",
            "id",               "",             DATA_INT,    sensor_id,
            "battery_ok",       "Battery",      DATA_INT,    battery_ok,
            "channel",          "Channel",      DATA_INT,    channel,
            "humidity",         "Humidity",     DATA_COND,   humidity != -1,    DATA_INT,    humidity,
            "temperature_C",    "Temperature",  DATA_COND,   humidity == -1,    DATA_FORMAT, "%.1f C", DATA_DOUBLE, temp_c,
            "mic",              "Integrity",    DATA_STRING, "PARITY",
            NULL);


    decoder_output_data(decoder, data);
    return 1;
}
