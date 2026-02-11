write_solid(Object dxobject,int triangle)
{
  Type type;
  int rank,shape[MAX_RANK];
  Array a;
  int np;
  int itab=1;
  float op;
  RGBColor *rgb;
  int pos_dim=3;
  float deltas[4];

  rgb =NULL; op = -1;

  a = (Array)DXGetComponentValue((Field)dxobject,"positions");
  if (!DXGetArrayInfo(a,&np,&type,NULL,&rank,shape))
    goto error;
  if (rank != 1 || shape[0] < 2){
    DXSetError(ERROR_DATA_INVALID,"positions must be 3-d or 2-d\n");
    goto error;
  }
  if (shape[0]==2){
    pos_dim = 2;

    if (DXQueryGridPositions(a,NULL,NULL,NULL,deltas)){
      if ((deltas[0]==0 || deltas[1]==0) || (deltas[2]==0 || deltas[3]==0))
        return (write_elevation(dxobject));
    }
  }


  fprintf(fp,"%s%s\n",tab[itab++],"Shape {");
  if (triangle == 0)
    fprintf(fp,"%s%s \n",tab[itab++],"geometry PointSet {");
  else if (triangle == 1)
    fprintf(fp,"%s%s \n",tab[itab++],"geometry IndexedLineSet {");
  else{
    fprintf(fp,"%s%s \n",tab[itab++],"geometry IndexedFaceSet {");
    fprintf(fp,"%s%s \n",tab[itab],"solid	FALSE");
    if (triangle == 3)
      fprintf(fp,"%s%s \n",tab[itab],"ccw	FALSE");
  }


  if (!write_positions(dxobject,itab,pos_dim))
    goto error;


  if (triangle > 0 ){
    if (!write_connections(dxobject,triangle,itab))
      goto error;
  }


  if (!write_colors(dxobject,itab,&rgb,&op))
    goto error;


  if (triangle > 1 && !write_normals(dxobject,itab))
    goto error;

  fprintf(fp,"%s}\n",tab[--itab]);


  write_appearence(rgb,op,triangle,itab);

  fprintf(fp,"%s}\n",tab[--itab]);

  return OK;

error: return ERROR;
}
