void _WM_DynamicVolumeAdjust(struct _mdi *mdi, int32_t *tmp_buffer, uint32_t buffer_used) {

    uint32_t i = 0;
    uint32_t j = 0;

    int8_t peak_set = 0;
    int32_t prev_val = 0;
    uint32_t peak_ofs = 0;
    int32_t peak = mdi->dyn_vol_peak;

    double volume_to_reach = mdi->dyn_vol_to_reach;
    double volume = mdi->dyn_vol;
    double volume_adjust = mdi->dyn_vol_adjust;
    double tmp_output = 0.0;

#define MAX_DYN_VOL 1.0

    for (i = 0; i < buffer_used; i++) {
        if ((i == 0) || (i > peak_ofs)) {

            peak_set = 0;
            prev_val = peak;
            peak_ofs = 0;
            for (j = i; j < buffer_used; j++) {
                if (peak_set == 0) {

                    if (prev_val > tmp_buffer[j]) {

                        peak_set = -1;
                    } else if (prev_val < tmp_buffer[j]) {

                        peak_set = 1;
                    } else {

                        prev_val = tmp_buffer[j];
                        continue;
                    }
                }

                if (peak_set == 1) {

                    if (peak < tmp_buffer[j]) {
                        peak = tmp_buffer[j];
                        peak_ofs = j;
                    } else if (peak > tmp_buffer[j]) {

                        break;
                    }
                } else {

                    if (peak > tmp_buffer[j]) {
                        peak = tmp_buffer[j];
                        peak_ofs = j;
                    } else if (peak < tmp_buffer[j]) {

                        break;
                    }
                }

                prev_val = tmp_buffer[j];
            }

            if (peak_set != 0) {
                if (peak_set == 1) {
                    if (peak > 32767) {
                        volume_to_reach = 32767.0 / (double)peak;
                    } else {
                        volume_to_reach = MAX_DYN_VOL;
                    }
                } else {
                    if (peak < -32768) {
                        volume_to_reach = -32768.0 / (double)peak;
                    } else {
                        volume_to_reach = MAX_DYN_VOL;
                    }
                }
            } else {

                volume_to_reach = MAX_DYN_VOL;
            }

            if (volume != volume_to_reach) {
                if (volume_to_reach == MAX_DYN_VOL) {

                    volume_adjust = (volume_to_reach - volume) / ((double)_WM_SampleRate * 0.1);
                } else {

                    volume_adjust = (volume_to_reach - volume) / ((double)_WM_SampleRate * 0.0001);
                }
            }
        }


        if ((volume_adjust != 0.0) && (volume != volume_to_reach)) {
                volume += volume_adjust;
                if (volume_adjust > 0.0) {

                    if (volume >= MAX_DYN_VOL) {

                        volume = MAX_DYN_VOL;
                        volume_adjust = 0.0;
                    } else if (volume > volume_to_reach) {

                        volume = volume_to_reach;
                        volume_adjust = 0.0;
                    }
                } else {

                    if (volume < volume_to_reach) {

                        volume = volume_to_reach;
                        volume_adjust = 0.0;
                    }
                }
            }


        tmp_output = (double)tmp_buffer[i] * volume;
        tmp_buffer[i] = (int32_t)tmp_output;
    }


    mdi->dyn_vol_adjust = volume_adjust;
    mdi->dyn_vol_peak = peak;
    mdi->dyn_vol = volume;
    mdi->dyn_vol_to_reach = volume_to_reach;
}
