static int acurite_rain_896_decode(r_device *decoder, bitbuffer_t *bitbuffer)
{
    uint8_t *b = bitbuffer->bb[0];
    int id;
    float total_rain;
    data_t *data;


    if (bitbuffer->bits_per_row[0] < 24)
        return DECODE_ABORT_LENGTH;

    if ((b[0] == 0) || (b[1] == 0) || (b[2] == 0) || (b[3] != 0) || (b[4] != 0))
        return DECODE_ABORT_EARLY;

    id = b[0];
    total_rain = ((b[1] & 0xf) << 8) | b[2];
    total_rain *= 0.5;

    decoder_logf(decoder, 2, __func__, "Total Rain is %2.1fmm", total_rain);
    decoder_log_bitrow(decoder, 2, __func__, b, bitbuffer->bits_per_row[0], "Raw Message ");


    data = data_make(
            "model",                "",             DATA_STRING, "Acurite-Rain",
            "id",                   "",             DATA_INT,    id,
            "rain_mm",              "Total Rain",   DATA_FORMAT, "%.1f mm", DATA_DOUBLE, total_rain,
            NULL);


    decoder_output_data(decoder, data);
    return 1;
}
