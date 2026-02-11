GSCWeights(char **aseq, int nseq, int alen, float *wgt)
{
  float **dmx;
  struct phylo_s *tree;
  float  *lwt, *rwt;
  float  *fwt;
  int      i;


  if (nseq == 1) { wgt[0] = 1.0; return; }


  MakeDiffMx(aseq, nseq, &dmx);
  if (! Cluster(dmx, nseq, CLUSTER_MIN, &tree))  Die("Cluster() failed");


  lwt = MallocOrDie (sizeof(float) * (2 * nseq - 1));
  rwt = MallocOrDie (sizeof(float) * (2 * nseq - 1));
  fwt = MallocOrDie (sizeof(float) * (2 * nseq - 1));


  for (i = 0; i < nseq; i++)
    lwt[i] = rwt[i] = 0.0;


  upweight(tree, nseq, lwt, rwt, nseq);


  fwt[nseq] = nseq;
  downweight(tree, nseq, lwt, rwt, fwt, nseq);

  for (i = 0; i < nseq; i++)
    wgt[i]  = fwt[i];

  FMX2Free(dmx);
  FreePhylo(tree, nseq);
  free(lwt); free(rwt); free(fwt);
}
