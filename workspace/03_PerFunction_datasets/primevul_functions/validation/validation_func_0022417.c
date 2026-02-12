static bool check_interleaving_with_nj(JOIN_TAB *next_tab)
{
  TABLE_LIST *next_emb= next_tab->table->pos_in_table_list->embedding;
  JOIN *join= next_tab->join;

  if (join->cur_embedding_map & ~next_tab->embedding_map)
  {


    return TRUE;
  }


  for (;next_emb && next_emb != join->emb_sjm_nest; next_emb= next_emb->embedding)
  {
    if (!next_emb->sj_on_expr)
    {
      next_emb->nested_join->counter++;
      if (next_emb->nested_join->counter == 1)
      {


        join->cur_embedding_map |= next_emb->nested_join->nj_map;
      }

      if (next_emb->nested_join->n_tables !=
          next_emb->nested_join->counter)
        break;


      join->cur_embedding_map &= ~next_emb->nested_join->nj_map;
    }
  }
  return FALSE;
}
