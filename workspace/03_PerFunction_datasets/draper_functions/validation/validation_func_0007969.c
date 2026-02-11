_get_mapped (GstBuffer * buffer, guint idx, GstMapInfo * info,
    GstMapFlags flags)
{
  GstMemory *mem, *mapped;

  mem = gst_memory_ref (GST_BUFFER_MEM_PTR (buffer, idx));

  mapped = gst_memory_make_mapped (mem, info, flags);

  if (mapped != mem) {

    gst_memory_lock (mapped, GST_LOCK_FLAG_EXCLUSIVE);
    GST_BUFFER_MEM_PTR (buffer, idx) = mapped;

    gst_memory_unlock (mem, GST_LOCK_FLAG_EXCLUSIVE);
  }
  gst_memory_unref (mem);

  return mapped;
}
