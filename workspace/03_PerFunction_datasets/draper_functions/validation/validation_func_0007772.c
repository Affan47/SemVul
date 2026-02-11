esl_keyhash_Dump(FILE *fp, const ESL_KEYHASH *kh)
{
  int idx;
  int h;
  int nkeys;
  int nempty  = 0;
  int maxkeys = -1;
  int minkeys = INT_MAX;

  for (h = 0; h < kh->hashsize; h++)
    {
      for (nkeys = 0, idx = kh->hashtable[h]; idx != -1; idx = kh->nxt[idx]) nkeys++;

      if (nkeys == 0)      nempty++;
      if (nkeys > maxkeys) maxkeys = nkeys;
      if (nkeys < minkeys) minkeys = nkeys;
    }

  fprintf(fp, "Total keys:             %d\n", kh->nkeys);
  fprintf(fp, "Hash table size:        %d\n", kh->hashsize);
  fprintf(fp, "Average occupancy:      %.2f\n", (float) kh->nkeys /(float) kh->hashsize);
  fprintf(fp, "Unoccupied slots:       %d\n", nempty);
  fprintf(fp, "Most in one slot:       %d\n", maxkeys);
  fprintf(fp, "Least in one slot:      %d\n", minkeys);
  fprintf(fp, "Keys allocated for:     %d\n", kh->kalloc);
  fprintf(fp, "Key string space alloc: %d\n", kh->salloc);
  fprintf(fp, "Key string space used:  %d\n", kh->sn);
  fprintf(fp, "Total obj size, bytes:  %d\n", (int) esl_keyhash_Sizeof(kh));
}
