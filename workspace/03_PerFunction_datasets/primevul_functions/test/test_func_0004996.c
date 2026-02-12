static int acurite_th_decode(r_device *decoder, bitbuffer_t *bitbuffer)
{
    uint8_t *bb = NULL;
    int cksum, battery_low, valid = 0;
    float tempc;
    uint8_t humidity, id, status;
    data_t *data;
    int result = 0;

    for (uint16_t brow = 0; brow < bitbuffer->num_rows; ++brow) {
        if (bitbuffer->bits_per_row[brow] != 40) {
            result = DECODE_ABORT_LENGTH;
            continue;
        }

        bb = bitbuffer->bb[brow];

        cksum = (bb[0] + bb[1] + bb[2] + bb[3]);

        if (cksum == 0 || ((cksum & 0xff) != bb[4])) {
            result = DECODE_FAIL_MIC;
            continue;
        }


        int temp_raw = (int16_t)(((bb[1] & 0x0f) << 12) | (bb[2] << 4));
        tempc        = (temp_raw >> 4) * 0.1f;
        id           = bb[0];
        status       = (bb[1] & 0xf0) >> 4;
        battery_low  = status & 0x8;
        humidity     = bb[3];


        data = data_make(
                "model",            "",             DATA_STRING, "Acurite-609TXC",
                "id",               "",             DATA_INT,    id,
                "battery_ok",       "Battery",      DATA_INT,    !battery_low,
                "temperature_C",    "Temperature",  DATA_FORMAT, "%.1f C", DATA_DOUBLE, tempc,
                "humidity",         "Humidity",     DATA_FORMAT, "%u %%", DATA_INT,    humidity,
                "status",           "",             DATA_INT,    status,
                "mic",              "Integrity",    DATA_STRING, "CHECKSUM",
                NULL);


        decoder_output_data(decoder, data);
        valid++;
    }

    if (valid)
        return 1;


    return result;
}
