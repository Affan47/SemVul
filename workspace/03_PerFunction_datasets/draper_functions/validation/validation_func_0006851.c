gsicc_mcm_monitor_rgb(void *inputcolor, int num_bytes)
{
    if (num_bytes == 1) {
        byte *rgb_val = (byte*) inputcolor;
        int rg_diff = (int) abs((int) rgb_val[0] - (int) rgb_val[1]);
        int rb_diff = (int) abs((int) rgb_val[0] - (int) rgb_val[2]);
        int bg_diff = (int) abs((int) rgb_val[1] - (int) rgb_val[2]);
        return (rg_diff < DEV_NEUTRAL_8 && rb_diff < DEV_NEUTRAL_8
                && bg_diff < DEV_NEUTRAL_8);
    } else {
        unsigned short *rgb_val = (unsigned short*) inputcolor;
        int rg_diff = (int) abs((int) rgb_val[0] - (int) rgb_val[1]);
        int rb_diff = (int) abs((int) rgb_val[0] - (int) rgb_val[2]);
        int bg_diff = (int) abs((int) rgb_val[1] - (int) rgb_val[2]);
        return (rg_diff < DEV_NEUTRAL_16 && rb_diff < DEV_NEUTRAL_16
                && bg_diff < DEV_NEUTRAL_16);
    }
}
