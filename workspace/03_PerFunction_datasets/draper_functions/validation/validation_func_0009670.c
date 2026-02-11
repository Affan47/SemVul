_backup_video_scale_orc_downsample_u16 (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_union16 * ORC_RESTRICT ptr0;
  const orc_union32 * ORC_RESTRICT ptr4;
  orc_union32 var34;
  orc_union16 var35;
  orc_union16 var36;
  orc_union16 var37;

  ptr0 = (orc_union16 *)ex->arrays[0];
  ptr4 = (orc_union32 *)ex->arrays[4];


  for (i = 0; i < n; i++) {

    var34 = ptr4[i];

    {
       orc_union32 _src;
       _src.i = var34.i;
       var36.i = _src.x2[1];
       var37.i = _src.x2[0];
    }

    var35.i = ((orc_uint16)var36.i + (orc_uint16)var37.i + 1)>>1;

    ptr0[i] = var35;
  }

}
