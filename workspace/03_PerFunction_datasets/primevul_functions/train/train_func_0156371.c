add_offset (guint64 offset, guint64 advance)
{

  if (offset > G_MAXUINT64 - advance)
    return G_MAXUINT64;
  return offset + advance;
}
