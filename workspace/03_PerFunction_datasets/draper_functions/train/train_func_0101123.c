_backup_orc_audio_convert_pack_s32_float_swap (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_union32 * ORC_RESTRICT ptr0;
  const orc_union32 * ORC_RESTRICT ptr4;
  orc_union32 var33;
#if defined(__APPLE__) && __GNUC__ == 4 && __GNUC_MINOR__ == 2 && defined (__i386__)
  volatile orc_union32 var34;
#else
  orc_union32 var34;
#endif
  orc_union32 var35;
  orc_union32 var36;
  orc_union32 var37;

  ptr0 = (orc_union32 *)ex->arrays[0];
  ptr4 = (orc_union32 *)ex->arrays[4];


    var34.i = (int)0x4f000000;

  for (i = 0; i < n; i++) {

    var33 = ptr4[i];

    var36.f = var33.i;

    {
       orc_union32 _src1;
       orc_union32 _src2;
       orc_union32 _dest1;
       _src1.i = ORC_DENORMAL(var36.i);
       _src2.i = ORC_DENORMAL(var34.i);
       _dest1.f = _src1.f / _src2.f;
       var37.i = ORC_DENORMAL(_dest1.i);
    }

    var35.i = ORC_SWAP_L(var37.i);

    ptr0[i] = var35;
  }

}
