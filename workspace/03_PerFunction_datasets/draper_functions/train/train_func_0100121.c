scale_and_shuffle_up3(jxr_image_t image)
{
    int mx;
    int my = image->cur_my + 3;
    int ch;


    switch (image->use_clr_fmt) {
        case 0:
            break;
        case 1:
            if (image->output_clr_fmt == JXR_OCF_RGB)
                yuv422_to_yuv420_up3(image);
            break;
        case 2:
            break;
        case 3:
            break;
        case 6:
            break;
    }
    for (mx = 0 ; mx < (int) EXTENDED_WIDTH_BLOCKS(image) ; mx += 1) {

#if defined(DETAILED_DEBUG) && 1
        int jdx;
        for (ch = 0 ; ch < image->num_channels ; ch += 1) {
            int count = 256;
            if (ch > 0 && image->use_clr_fmt==2)
                count = 128;
            if (ch > 0 && image->use_clr_fmt==1)
                count = 64;

            DEBUG("image yuv mx=%3d my=%3d ch=%d:", mx, my, ch);
            for (jdx = 0 ; jdx < count ; jdx += 1) {
                if (jdx%8 == 0 && jdx != 0)
                    DEBUG("\n%*s", 29, "");
                DEBUG(" %08x", image->strip[ch].up3[mx].data[jdx]);
            }
            DEBUG("\n");
        }
#endif


        block_shuffle444(image->strip[0].up3[mx].data);
        for (ch = 1 ; ch < image->num_channels ; ch += 1) {
            switch (image->use_clr_fmt) {
                case 1:
                    block_shuffle420(image->strip[ch].up3[mx].data);
                    break;
                case 2:
                    block_shuffle422(image->strip[ch].up3[mx].data);
                    break;
                default:
                    block_shuffle444(image->strip[ch].up3[mx].data);
                    break;
            }
        }
    }
}
