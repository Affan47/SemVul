static int acurite_606_decode(r_device *decoder, bitbuffer_t *bitbuffer)
{
    data_t *data;
    uint8_t *b;
    int row;
    int16_t temp_raw;
    float temp_c;
    int battery_ok;
    int sensor_id;

    row = bitbuffer_find_repeated_row(bitbuffer, 3, 32);
    if (row < 0)
        return DECODE_ABORT_EARLY;

    if (bitbuffer->bits_per_row[row] > 33)
        return DECODE_ABORT_LENGTH;

    b = bitbuffer->bb[row];

    if (b[4] != 0)
        return DECODE_FAIL_SANITY;


    if (b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 0)
        return DECODE_FAIL_SANITY;


    uint8_t chk = lfsr_digest8(b, 3, 0x98, 0xf1);
    if (chk != b[3])
        return DECODE_FAIL_MIC;


    sensor_id  = b[0];
    battery_ok = (b[1] & 0x80) >> 7;
    temp_raw   = (int16_t)((b[1] << 12) | (b[2] << 4));
    temp_raw   = temp_raw >> 4;
    temp_c     = temp_raw * 0.1f;


    data = data_make(
            "model",            "",             DATA_STRING, "Acurite-606TX",
            "id",               "",             DATA_INT, sensor_id,
            "battery_ok",       "Battery",      DATA_INT,    battery_ok,
            "temperature_C",    "Temperature",  DATA_FORMAT, "%.1f C", DATA_DOUBLE, temp_c,
            "mic",              "Integrity",    DATA_STRING, "CHECKSUM",
            NULL);


    decoder_output_data(decoder, data);
    return 1;
}
