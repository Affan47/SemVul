optimize_code3(FILE *lf)
{
  unsigned i, j, k;
  int changed = 0;
  code_t *c0, *c1;

  for(i = 0; i < dict_size; i++) {
    if(
      i >= sizeof prim_names / sizeof *prim_names &&
      !dict[i].del &&
      !dict[i].ref &&
      dict[i].def == 1 &&
      dict[i].type == t_none
    ) {
      c0 = code + (j = dict[i].def_idx);
      c1 = code + next_code(j);

      if(c1 == c0) continue;

      if(
        c0->type == t_dict_idx &&
        c0->value.u == i &&
        c1->type == t_code &&
        code[j = skip_code(c1->value.u)].type == t_prim &&
        code[j].value.u == p_def &&
        j > dict[i].def_idx
      ) {
        if(verbose && lf) fprintf(lf, "#   defined but unused: %s (index %d)\n", dict[i].name, i);
        if(verbose && lf) fprintf(lf, "#   deleting code: %d - %d\n", dict[i].def_idx, j);
        for(k = dict[i].def_idx; k <= j; k++) code[k].type = t_skip;
        dict[i].del = 1;

        changed = 1;
      }
    }
  }

  return changed;
}
