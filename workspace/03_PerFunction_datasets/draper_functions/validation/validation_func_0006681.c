flag_parens(chunk_t *po, UINT64 flags,
                            c_token_t opentype, c_token_t parenttype,
                            bool parent_all)
{
   chunk_t *paren_close;
   chunk_t *pc;

   if (is_oc_block(po))
   {
      return(NULL);
   }

   paren_close = chunk_skip_to_match(po, CNAV_PREPROC);
   if (paren_close == NULL)
   {
      LOG_FMT(LERR, "%s: no match for [%.*s] at  [%d:%d]\n",
              __func__, po->len, po->str, po->orig_line, po->orig_col);
      return(NULL);
   }

   if ((paren_close != NULL) && (po != paren_close))
   {
      if ((flags != 0) ||
          (parent_all && (parenttype != CT_NONE)))
      {
         for (pc = chunk_get_next(po, CNAV_PREPROC);
              pc != paren_close;
              pc = chunk_get_next(pc, CNAV_PREPROC))
         {
            pc->flags |= flags;
            if (parent_all)
            {
               pc->parent_type = parenttype;
            }
         }
      }

      if (opentype != CT_NONE)
      {
         po->type          = opentype;
         paren_close->type = (c_token_t)(opentype + 1);
      }

      if (parenttype != CT_NONE)
      {
         po->parent_type          = parenttype;
         paren_close->parent_type = parenttype;
      }
   }
   return(chunk_get_next_ncnl(paren_close, CNAV_PREPROC));
}
