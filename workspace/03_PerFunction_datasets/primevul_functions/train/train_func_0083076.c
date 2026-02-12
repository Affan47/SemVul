jbig2_image_compose(Jbig2Ctx *ctx, Jbig2Image *dst, Jbig2Image *src, int x, int y, Jbig2ComposeOp op)
{
    uint32_t w, h;
    uint32_t shift;
    uint32_t leftbyte;
    uint8_t *ss;
    uint8_t *dd;
    uint8_t leftmask, rightmask;
    int early = x >= 0;
    int late;
    uint32_t bytewidth;
    uint32_t syoffset = 0;

    if (src == NULL)
        return 0;


    w = src->width;
    h = src->height;
    shift = (x & 7);
    ss = src->data - early;

    if (x < 0) {
        if (w < (uint32_t) -x)
            w = 0;
        else
            w += x;
        ss += (-x-1)>>3;
        x = 0;
    }
    if (y < 0) {
        if (h < (uint32_t) -y)
            h = 0;
        else
            h += y;
        syoffset = -y * src->stride;
        y = 0;
    }
    if ((uint32_t)x + w > dst->width)
    {
        if (dst->width < (uint32_t)x)
            w = 0;
        else
            w = dst->width - x;
    }
    if ((uint32_t)y + h > dst->height)
    {
        if (dst->height < (uint32_t)y)
            h = 0;
        else
            h = dst->height - y;
    }
#ifdef JBIG2_DEBUG
    jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, -1, "compositing %dx%d at (%d, %d) after clipping", w, h, x, y);
#endif


    if ((w <= 0) || (h <= 0)) {
#ifdef JBIG2_DEBUG
        jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, -1, "zero clipping region");
#endif
        return 0;
    }

    leftbyte = (uint32_t) x >> 3;
    dd = dst->data + y * dst->stride + leftbyte;
    bytewidth = (((uint32_t) x + w - 1) >> 3) - leftbyte + 1;
    leftmask = 255>>(x&7);
    rightmask = (((x+w)&7) == 0) ? 255 : ~(255>>((x+w)&7));
    if (bytewidth == 1)
        leftmask &= rightmask;
    late = (ss + bytewidth >= src->data + ((src->width+7)>>3));
    ss += syoffset;

    switch(op)
    {
    case JBIG2_COMPOSE_OR:
        jbig2_image_compose_opt_OR(ss, dd, early, late, leftmask, rightmask, bytewidth, h, shift, dst->stride, src->stride);
        break;
    case JBIG2_COMPOSE_AND:
        jbig2_image_compose_opt_AND(ss, dd, early, late, leftmask, rightmask, bytewidth, h, shift, dst->stride, src->stride);
        break;
    case JBIG2_COMPOSE_XOR:
        jbig2_image_compose_opt_XOR(ss, dd, early, late, leftmask, rightmask, bytewidth, h, shift, dst->stride, src->stride);
        break;
    case JBIG2_COMPOSE_XNOR:
        jbig2_image_compose_opt_XNOR(ss, dd, early, late, leftmask, rightmask, bytewidth, h, shift, dst->stride, src->stride);
        break;
    case JBIG2_COMPOSE_REPLACE:
        jbig2_image_compose_opt_REPLACE(ss, dd, early, late, leftmask, rightmask, bytewidth, h, shift, dst->stride, src->stride);
        break;
    }

    return 0;
}
