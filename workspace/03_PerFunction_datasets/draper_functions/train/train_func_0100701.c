gst_shm_sink_allocator_mem_is_span (GstMemory * mem1, GstMemory * mem2,
    gsize * offset)
{
  GstShmSinkMemory *mymem1 = (GstShmSinkMemory *) mem1;
  GstShmSinkMemory *mymem2 = (GstShmSinkMemory *) mem2;

  if (offset) {
    GstMemory *parent;

    parent = mem1->parent;

    *offset = mem1->offset - parent->offset;
  }


  return mymem1->data + mem1->offset + mem1->size ==
      mymem2->data + mem2->offset;
}
