unpack_I422_10LE (const GstVideoFormatInfo * info, GstVideoPackFlags flags,
    gpointer dest, const gpointer data[GST_VIDEO_MAX_PLANES],
    const gint stride[GST_VIDEO_MAX_PLANES], gint x, gint y, gint width)
{
  int i;
  guint16 *srcY = GET_Y_LINE (y);
  guint16 *srcU = GET_U_LINE (y);
  guint16 *srcV = GET_V_LINE (y);
  guint16 *d = dest, Y, U, V;

  for (i = 0; i < width; i++) {
    Y = GST_READ_UINT16_LE (srcY + i) << 6;
    U = GST_READ_UINT16_LE (srcU + (i >> 1)) << 6;
    V = GST_READ_UINT16_LE (srcV + (i >> 1)) << 6;

    if (!(flags & GST_VIDEO_PACK_FLAG_TRUNCATE_RANGE)) {
      Y |= (Y >> 10);
      U |= (U >> 10);
      V |= (V >> 10);
    }

    d[i * 4 + 0] = 0xffff;
    d[i * 4 + 1] = Y;
    d[i * 4 + 2] = U;
    d[i * 4 + 3] = V;
  }
}
