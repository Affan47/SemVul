init_global(int32 xdim, int32 ydim, VOIDP out, VOIDP out_pal)
{
    int32       i, j;


    image = (unsigned char *) out;
    new_pal = (unsigned char *) out_pal;
    if (color_pt)
        HDfree((VOIDP) color_pt);
    color_pt = (struct rgb *) HDmalloc((unsigned) ((xdim * ydim) / 8) *
                                         sizeof(struct rgb));

    if (image == NULL || color_pt == NULL || new_pal == NULL)
      {
          return;
      }


    for (i = 0; i < (xdim * ydim / 4); i++)
        image[i] = 0;

    for (i = 0; i < (xdim * ydim / 8); i++)
        for (j = RED; j <= BLUE; j++)
            color_pt[i].c[j] = 0;

    for (i = 0; i < MAXCOLOR; i++)
        trans[i] = -1;
}
