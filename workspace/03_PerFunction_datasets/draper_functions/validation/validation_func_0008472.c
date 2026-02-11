write_positions(Object dxobject,int itab,int pos_dim)
{
  int i;
  Array a;
  int np,rank,shape[MAX_RANK];
  Type type;
  float *f;

  a = (Array)DXGetComponentValue((Field)dxobject,"positions");
  if (!DXGetArrayInfo(a,&np,&type,NULL,&rank,shape))
    goto error;
  fprintf(fp,"%s%s\n",tab[itab++],"coord Coordinate{ ");
  fprintf(fp,"%s%s\n",tab[itab++],"point [ ");
  f = (float *)DXGetArrayData(a);
  if (pos_dim == 2){
    for (i=0; i<np; i++)
      fprintf(fp,"%s%f %f 0.0\n", tab[itab],f[i*2], f[i*2 +1] );
  }
  else{
    for (i=0; i<np; i++)
      fprintf(fp,"%s%f %f %f\n", tab[itab],f[i*3], f[i*3 +1], f[i*3 +2]);
  }
  fprintf(fp,"%s%s\n",tab[--itab],"]");
  fprintf(fp,"%s%s\n",tab[--itab],"}");

  return OK;
error:
  return ERROR;
}
