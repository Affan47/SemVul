wavpack_type_find (GstTypeFind * tf, gpointer unused)
{
  GstTypeFindProbability base_prob = GST_TYPE_FIND_POSSIBLE;
  guint64 offset;
  guint32 blocksize;
  const guint8 *data;
  guint count_wv, count_wvc;

  data = gst_type_find_peek (tf, 0, 32);
  if (!data)
    return;

  if (data[0] != 'w' || data[1] != 'v' || data[2] != 'p' || data[3] != 'k')
    return;


  blocksize = GST_READ_UINT32_LE (data + 4);
  GST_LOG ("wavpack header, blocksize=0x%04x", blocksize);
  count_wv = 0;
  count_wvc = 0;
  offset = 32;
  while (offset < 8 + blocksize) {
    guint32 sublen;


    GST_LOG ("peeking at chunk at offset 0x%04x", (guint) offset);
    data = gst_type_find_peek (tf, offset, 4);
    if (data == NULL)
      break;
    sublen = ((guint32) data[1]) << 1;
    if (data[0] & 0x80) {
      sublen |= (((guint32) data[2]) << 9) | (((guint32) data[3]) << 17);
      sublen += 1 + 3;
    } else {
      sublen += 1 + 1;
    }
    if (offset + sublen > 8 + blocksize) {
      GST_LOG ("chunk length too big (%u > %" G_GUINT64_FORMAT ")", sublen,
          blocksize - offset);
      break;
    }
    if ((data[0] & 0x20) == 0) {
      switch (data[0] & 0x0f) {
        case 0xa:
        case 0xc:
          ++count_wv;
          break;
        case 0xb:
          ++count_wvc;
          break;
        default:
          break;
      }
      if (count_wv >= 5 || count_wvc >= 5)
        break;
    }
    offset += sublen;
  }


  data = gst_type_find_peek (tf, 8 + blocksize, 4);
  if (data != NULL && memcmp (data, "wvpk", 4) == 0) {
    GST_DEBUG ("found second block sync");
    base_prob = GST_TYPE_FIND_LIKELY;
  }

  GST_DEBUG ("wvc=%d, wv=%d", count_wvc, count_wv);

  if (count_wvc > 0 && count_wvc > count_wv) {
    gst_type_find_suggest (tf,
        MIN (base_prob + 5 * count_wvc, GST_TYPE_FIND_NEARLY_CERTAIN),
        WAVPACK_CORRECTION_CAPS);
  } else if (count_wv > 0) {
    gst_type_find_suggest (tf,
        MIN (base_prob + 5 * count_wv, GST_TYPE_FIND_NEARLY_CERTAIN),
        WAVPACK_CAPS);
  }
}
