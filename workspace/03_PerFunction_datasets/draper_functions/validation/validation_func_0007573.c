set_insn_start(struct st_translate *t, unsigned start)
{
   if (t->insn_count + 1 >= t->insn_size) {
      t->insn_size = 1 << (util_logbase2(t->insn_size) + 1);
      t->insn = (unsigned *)realloc(t->insn, t->insn_size * sizeof(t->insn[0]));
      if (t->insn == NULL) {
         t->error = TRUE;
         return;
      }
   }

   t->insn[t->insn_count++] = start;
}
