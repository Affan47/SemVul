box_blur_line (gint box_width, gint even_offset,
               guchar *src, guchar *dest,
               gint len, gint bpp)
{
    gint  i;
    gint  lead;
    gint  output;
    gint  trail;

    gint  *ac;

    g_assert (box_width > 0);

    ac = g_new0 (gint, bpp);


    lead = 0;

    if (box_width % 2 != 0) {

        output = lead - (box_width - 1) / 2;
        trail  = lead - box_width;
    } else {

        if (even_offset == 1) {

            output = lead + 1 - box_width / 2;
            trail  = lead - box_width;
        } else if (even_offset == -1) {

            output = lead - box_width / 2;
            trail  = lead - box_width;
        } else {

            g_assert_not_reached ();
        }
    }


    for (i = 0; i < bpp; i++)
        ac[i] = 0;


    while (output < len) {


        guint coverage = (lead < len ? lead : len - 1) - (trail >= 0 ? trail : -1);

#ifdef READABLE_BOXBLUR_CODE


        for (i = 0; i < bpp; i++) {


            if (lead < len)
                ac[i] += src[bpp * lead + i];


            if (trail >= 0)
                ac[i] -= src[bpp * trail + i];


            if (output >= 0)
                dest[bpp * output + i] = (ac[i] + (coverage >> 1)) / coverage;
        }
#endif


        if (lead < len) {
            if (trail >= 0) {


                for (i = 0; i < bpp; i++) {
                    ac[i] += src[bpp * lead + i];
                    ac[i] -= src[bpp * trail + i];
                    dest[bpp * output + i] = (ac[i] + (coverage >> 1)) / coverage;
                }
            } else if (output >= 0) {


                for (i = 0; i < bpp; i++) {
                    ac[i] += src[bpp * lead + i];
                    dest[bpp * output + i] = (ac[i] + (coverage >> 1)) / coverage;
                }
            } else {


                for (i = 0; i < bpp; i++)
                    ac[i] += src[bpp * lead + i];
            }
        } else if (trail >= 0) {


            for (i = 0; i < bpp; i++) {
                ac[i] -= src[bpp * trail + i];
                dest[bpp * output + i] = (ac[i] + (coverage >> 1)) / coverage;
            }
        } else if (output >= 0) {


            for (i = 0; i < bpp; i++)
                dest[bpp * output + i] = (ac[i] + (coverage >> 1)) / coverage;
        }

        lead++;
        output++;
        trail++;
    }

    g_free (ac);
}
