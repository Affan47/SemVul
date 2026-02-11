d_mass_scalar( FMField *out, FMField *stateP, FMField *stateQ,
		     FMField *bf, VolumeGeometry *vg,
		     int32 *conn, int32 nEl, int32 nEP,
		     int32 *elList, int32 elList_nRow )
{
  int32 ii, iel, dim, nQP, ret = RET_OK;
  FMField *st = 0, *fp = 0, *ftfp = 0;

  nQP = vg->bfGM->nLev;
  dim = vg->bfGM->nRow;

  fmf_createAlloc( &st, 1, 1, 1, nEP );
  fmf_createAlloc( &fp, 1, nQP, 1, 1 );
  fmf_createAlloc( &ftfp, 1, nQP, nEP, 1 );

  for (ii = 0; ii < elList_nRow; ii++) {
    iel = elList[ii];

    FMF_SetCell( out, ii );
    FMF_SetCell( vg->det, iel );

    ele_extractNodalValuesDBD( st, stateP, conn + nEP * iel );

    bf_act( fp, bf, st );
    bf_actt( ftfp, bf, fp );

    ele_extractNodalValuesDBD( st, stateQ, conn + nEP * iel );
    fmf_mulATB_1n( fp, st, ftfp );

    fmf_sumLevelsMulF( out, fp, vg->det->val );

    ERR_CheckGo( ret );
  }

 end_label:
  fmf_freeDestroy( &st );
  fmf_freeDestroy( &fp );
  fmf_freeDestroy( &ftfp );

  return( ret );
}
