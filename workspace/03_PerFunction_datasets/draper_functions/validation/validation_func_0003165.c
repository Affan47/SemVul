reset_trx_data(ecif_EdgeGeometry_X& tx)
{
  delete[] tx.start;
  delete[] tx.end;
  delete[] tx.definingPoints;
  delete[] tx.pointVertexFlags;
  delete[] tx.location;
  delete[] tx.knots;
  delete[] tx.cpoints;
  purgeMatcValueTable(tx.matcTable);
  init_trx_data(tx);
}
