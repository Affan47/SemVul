static void  Ins_JMPR( INS_ARG )
  {
    if ( BOUNDS(CUR.IP + args[0], CUR.codeSize ) )
    {
      CUR.error = TT_Err_Invalid_Reference;
      return;
    }

    CUR.IP      += (Int)(args[0]);
    CUR.step_ins = FALSE;

    if(CUR.IP > CUR.codeSize ||
       (CUR.code[CUR.IP] != 0x2D && CUR.code[CUR.IP - 1] == 0x2D))


      CUR.IP -= 1;
  }
