channel_decorrelation(FlacEncodeContext *ctx)
{
    FlacFrame *frame;
    int32_t *left, *right;
    int i, n;

    frame = &ctx->frame;
    n = frame->blocksize;
    left  = frame->subframes[0].samples;
    right = frame->subframes[1].samples;

    if(ctx->channels != 2) {
        frame->ch_mode = FLAC_CHMODE_NOT_STEREO;
        return;
    }

    frame->ch_mode = estimate_stereo_mode(left, right, n);


    if(frame->ch_mode == FLAC_CHMODE_LEFT_RIGHT) {
        return;
    }
    if(frame->ch_mode == FLAC_CHMODE_MID_SIDE) {
        int32_t tmp;
        for(i=0; i<n; i++) {
            tmp = left[i];
            left[i] = (tmp + right[i]) >> 1;
            right[i] = tmp - right[i];
        }
        frame->subframes[1].obits++;
    } else if(frame->ch_mode == FLAC_CHMODE_LEFT_SIDE) {
        for(i=0; i<n; i++) {
            right[i] = left[i] - right[i];
        }
        frame->subframes[1].obits++;
    } else {
        for(i=0; i<n; i++) {
            left[i] -= right[i];
        }
        frame->subframes[0].obits++;
    }
}
