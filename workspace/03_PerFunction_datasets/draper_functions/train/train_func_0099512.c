_backup_cogorc_planar_chroma_420_422 (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int j;
  int n = ex->n;
  int m = ex->params[ORC_VAR_A1];
  orc_int8 * ORC_RESTRICT ptr0;
  orc_int8 * ORC_RESTRICT ptr1;
  const orc_int8 * ORC_RESTRICT ptr4;
  orc_int8 var32;
  orc_int8 var33;
  orc_int8 var34;
  orc_int8 var35;

  for (j = 0; j < m; j++) {
    ptr0 = ORC_PTR_OFFSET(ex->arrays[0], ex->params[0] * j);
    ptr1 = ORC_PTR_OFFSET(ex->arrays[1], ex->params[1] * j);
    ptr4 = ORC_PTR_OFFSET(ex->arrays[4], ex->params[4] * j);


    for (i = 0; i < n; i++) {

      var32 = ptr4[i];

      var33 = var32;

      ptr0[i] = var33;

      var34 = ptr4[i];

      var35 = var34;

      ptr1[i] = var35;
    }
  }

}
