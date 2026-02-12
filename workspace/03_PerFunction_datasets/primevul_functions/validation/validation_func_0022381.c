void set_join_cache_denial(JOIN_TAB *join_tab)
{
  if (join_tab->cache)
  {


    if (join_tab->cache->prev_cache)
      join_tab->cache->prev_cache->next_cache= 0;


    if (join_tab->cache->next_cache)
      join_tab->cache->next_cache->prev_cache= 0;

    join_tab->cache->free();
    join_tab->cache= 0;
  }
  if (join_tab->use_join_cache)
  {
    join_tab->use_join_cache= FALSE;
    join_tab->used_join_cache_level= 0;


    join_tab[-1].next_select= sub_select;
    if (join_tab->type == JT_REF && join_tab->is_ref_for_hash_join())
    {
      join_tab->type= JT_ALL;
      join_tab->ref.key_parts= 0;
    }
    join_tab->join->return_tab= join_tab;
  }
}
