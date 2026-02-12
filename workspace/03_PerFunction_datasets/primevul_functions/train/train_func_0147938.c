pututf8(struct ly_ctx *ctx, char *dst, int32_t value)
{
    if (value < 0x80) {

        if (value < 0x20 &&
                value != 0x09 &&
                value != 0x0a &&
                value != 0x0d) {
            goto error;
        }

        dst[0] = value;
        return 1;
    } else if (value < 0x800) {

        dst[0] = 0xc0 | (value >> 6);
        dst[1] = 0x80 | (value & 0x3f);
        return 2;
    } else if (value < 0xfffe) {

        if (((value & 0xf800) == 0xd800) ||
                (value >= 0xfdd0 && value <= 0xfdef)) {


            goto error;
        }

        dst[0] = 0xe0 | (value >> 12);
        dst[1] = 0x80 | ((value >> 6) & 0x3f);
        dst[2] = 0x80 | (value & 0x3f);

        return 3;
    } else if (value < 0x10fffe) {
        if ((value & 0xffe) == 0xffe) {


            goto error;
        }

        dst[0] = 0xf0 | (value >> 18);
        dst[1] = 0x80 | ((value >> 12) & 0x3f);
        dst[2] = 0x80 | ((value >> 6) & 0x3f);
        dst[3] = 0x80 | (value & 0x3f);

        return 4;
    }

error:

    LOGVAL(ctx, LYE_XML_INCHAR, LY_VLOG_NONE, NULL, NULL);
    LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Invalid UTF-8 value 0x%08x", value);
    return 0;
}
