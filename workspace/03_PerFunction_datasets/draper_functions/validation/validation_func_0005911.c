trace_lookup (unw_cursor_t *cursor,
	      unw_trace_cache_t *cache,
	      unw_word_t cfa,
	      unw_word_t rip,
	      unw_word_t rbp,
	      unw_word_t rsp)
{


  uint64_t i, addr;
  uint64_t cache_size = 1u << cache->log_size;
  uint64_t slot = ((rip * 0x9e3779b97f4a7c16) >> 43) & (cache_size-1);
  unw_tdep_frame_t *frame;

  for (i = 0; i < 16; ++i)
  {
    frame = &cache->frames[slot];
    addr = frame->virtual_address;


    if (likely(addr == rip))
    {
      Debug (4, "found address after %ld steps\n", i);
      return frame;
    }


    if (likely(! addr))
      break;


    if (++slot >= cache_size)
      slot -= cache_size;
  }


  Debug (4, "updating slot %lu after %ld steps, replacing 0x%lx\n", slot, i, addr);
  if (unlikely(addr || cache->used >= cache_size / 2))
  {
    if (unlikely(trace_cache_expand (cache) < 0))
      return 0;

    cache_size = 1u << cache->log_size;
    slot = ((rip * 0x9e3779b97f4a7c16) >> 43) & (cache_size-1);
    frame = &cache->frames[slot];
    addr = frame->virtual_address;
  }

  if (! addr)
    ++cache->used;

  return trace_init_addr (frame, cursor, cfa, rip, rbp, rsp);
}
