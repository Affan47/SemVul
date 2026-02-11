parse_cr_string(chunk_t *pc, int q_idx)
{
   int        idx     = q_idx + 1;
   const char *tag    = &pc->str[idx];
   int        tag_len = 0;

   while ((pc->str[idx] != 0) &&
          (pc->str[idx] != '('))
   {
      tag_len++;
      idx++;
   }
   if (pc->str[idx] != '(')
   {
      return(false);
   }

   pc->type = CT_STRING;
   cpd.column += idx;
   while (pc->str[idx] != 0)
   {
      if ((pc->str[idx] == ')') &&
          (memcmp(&pc->str[idx + 1], tag, tag_len) == 0) &&
          (pc->str[idx + tag_len + 1] == '"'))
      {
         idx        += tag_len + 2;
         cpd.column += tag_len + 2;

         pc->len     = idx;
         parse_suffix(pc);
         return(true);
      }
      if (pc->str[idx] == '\n')
      {
         cpd.column = 1;
         cpd.line_number++;
         pc->nl_count++;
         pc->type = CT_STRING_MULTI;
      }
      else
      {
         cpd.column++;
      }

      idx++;
   }
   return(false);
}
