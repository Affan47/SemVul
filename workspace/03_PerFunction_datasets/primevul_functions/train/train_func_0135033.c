nm_wifi_utils_level_to_quality(int val)
{
    if (val < 0) {

        val = abs(CLAMP(val, -100, -40) + 40);
        val = 100 - (int) ((100.0 * (double) val) / 60.0);
    } else if (val > 110 && val < 256) {

        val -= 256;
        val = abs(CLAMP(val, -100, -40) + 40);
        val = 100 - (int) ((100.0 * (double) val) / 60.0);
    } else {

    }

    return CLAMP(val, 0, 100);
}
