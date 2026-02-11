align_trailing_comments(chunk_t *start)
{
   int          min_col  = 0;
   int          min_orig = -1;
   chunk_t      *pc      = start;
   int          nl_count = 0;
   ChunkStack   cs;
   CmtAlignType cmt_type_start, cmt_type_cur;
   int          col;
   int          intended_col = cpd.settings[UO_align_right_cmt_at_col].n;

   cmt_type_start = get_comment_align_type(pc);

   LOG_FMT(LALADD, "%s: start on line=%d\n", __func__, pc->orig_line);


   while ((pc != NULL) && (nl_count < cpd.settings[UO_align_right_cmt_span].n))
   {
      if (((pc->flags & PCF_RIGHT_COMMENT) != 0) && (pc->column > 1))
      {
         cmt_type_cur = get_comment_align_type(pc);

         if (cmt_type_cur == cmt_type_start)
         {
            col = 1 + (pc->brace_level * cpd.settings[UO_indent_columns].n);
            LOG_FMT(LALADD, "%s: line=%d col=%d max_col=%d pc->col=%d pc->len=%d %s\n",
                    __func__, pc->orig_line, col, min_col, pc->column, pc->len,
                    get_token_name(pc->type));
            if ((min_orig < 0) || (min_orig > pc->column))
            {
               min_orig = pc->column;
            }
            if (pc->column < col)
            {
               pc->column = col;
            }
            align_add(cs, pc, min_col, 1, true);
            nl_count = 0;
         }
      }
      if (chunk_is_newline(pc))
      {
         nl_count += pc->nl_count;
      }
      pc = chunk_get_next(pc);
   }


   col = min_orig;

   if ((intended_col > 0) && (col > intended_col))
   {
      col = intended_col;
   }

   if (col < min_col)
   {
      col = min_col;
   }

   if (col < intended_col)
   {
      col = intended_col;
   }
   LOG_FMT(LALADD, "%s:  -- min_orig=%d intend=%d min_allowed=%d ==> col=%d\n", __func__,
           min_orig, intended_col, min_col, col);
   align_stack(cs, col, (intended_col != 0), LALTC);

   return(chunk_get_next(pc));
}
