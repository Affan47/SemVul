freeGroup(bdescr *p)
{
  nat ln;


  ASSERT(p->free != (P_)-1);

  p->free = (void *)-1;
  p->gen = NULL;
  p->gen_no = 0;

  IF_DEBUG(sanity,memset(p->start, 0xaa, (W_)p->blocks * BLOCK_SIZE));

  if (p->blocks == 0) barf("freeGroup: block size is zero");

  if (p->blocks >= BLOCKS_PER_MBLOCK)
  {
      nat mblocks;

      mblocks = BLOCKS_TO_MBLOCKS(p->blocks);

      ASSERT(p->blocks == MBLOCK_GROUP_BLOCKS(mblocks));

      n_alloc_blocks -= mblocks * BLOCKS_PER_MBLOCK;

      free_mega_group(p);
      return;
  }

  ASSERT(n_alloc_blocks >= p->blocks);
  n_alloc_blocks -= p->blocks;


  {
      bdescr *next;
      next = p + p->blocks;
      if (next <= LAST_BDESCR(MBLOCK_ROUND_DOWN(p)) && next->free == (P_)-1)
      {
          p->blocks += next->blocks;
          ln = log_2(next->blocks);
          dbl_link_remove(next, &free_list[ln]);
          if (p->blocks == BLOCKS_PER_MBLOCK)
          {
              free_mega_group(p);
              return;
          }
          setup_tail(p);
      }
  }


  if (p != FIRST_BDESCR(MBLOCK_ROUND_DOWN(p)))
  {
      bdescr *prev;
      prev = p - 1;
      if (prev->blocks == 0) prev = prev->link;

      if (prev->free == (P_)-1)
      {
          ln = log_2(prev->blocks);
          dbl_link_remove(prev, &free_list[ln]);
          prev->blocks += p->blocks;
          if (prev->blocks >= BLOCKS_PER_MBLOCK)
          {
              free_mega_group(prev);
              return;
          }
          p = prev;
      }
  }

  setup_tail(p);
  free_list_insert(p);

  IF_DEBUG(sanity, checkFreeListSanity());
}
