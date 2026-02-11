default_goto (symbol_number sym, size_t state_count[])
{
  goto_number begin = goto_map[sym - ntokens];
  goto_number end = goto_map[sym - ntokens + 1];
  state_number res = -1;

  if (begin != end)
    {
      size_t max = 0;
      goto_number i;
      state_number s;

      for (s = 0; s < nstates; s++)
        state_count[s] = 0;

      for (i = begin; i < end; i++)
        state_count[to_state[i]]++;

      for (s = 0; s < nstates; s++)
        if (max < state_count[s])
          {
            max = state_count[s];
            res = s;
          }
    }
  return res;
}
