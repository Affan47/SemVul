gli_resize_mask(unsigned int x, unsigned int y)
{
    int i;

    if (!gli_mask)
    {
        gli_mask = (mask_t*) calloc(1, sizeof(mask_t));
        if (!gli_mask)
        {
            gli_strict_warning("resize_mask: out of memory");
            return;
        }
    }


    for (i = 0; i < gli_mask->hor; i++)
    {
        if (gli_mask->links[i])
            free(gli_mask->links[i]);
    }

    if (gli_mask->links)
        free(gli_mask->links);

    gli_mask->hor = x + 1;
    gli_mask->ver = y + 1;


    gli_mask->links = (glui32**) calloc(gli_mask->hor, sizeof(glui32*));
    if (!gli_mask->links)
    {
        gli_strict_warning("resize_mask: out of memory");
        gli_mask->hor = 0;
        gli_mask->ver = 0;
        return;
    }

    for (i = 0; i < gli_mask->hor; i++)
    {
        gli_mask->links[i] = (glui32*) calloc(gli_mask->ver, sizeof(glui32));
        if (!gli_mask->links[i])
        {
            gli_strict_warning("resize_mask: could not allocate new memory");
            return;
        }
    }

    gli_mask->select.x0 = 0;
    gli_mask->select.y0 = 0;
    gli_mask->select.x1 = 0;
    gli_mask->select.y1 = 0;

    return;
}
