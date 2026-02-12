u32 sqlite3VdbeSerialGet(
  const unsigned char *buf,
  u32 serial_type,
  Mem *pMem
){
  switch( serial_type ){
    case 10: {

      pMem->flags = MEM_Null|MEM_Zero;
      pMem->n = 0;
      pMem->u.nZero = 0;
      break;
    }
    case 11:
    case 0: {

      pMem->flags = MEM_Null;
      break;
    }
    case 1: {


      pMem->u.i = ONE_BYTE_INT(buf);
      pMem->flags = MEM_Int;
      testcase( pMem->u.i<0 );
      return 1;
    }
    case 2: {


      pMem->u.i = TWO_BYTE_INT(buf);
      pMem->flags = MEM_Int;
      testcase( pMem->u.i<0 );
      return 2;
    }
    case 3: {


      pMem->u.i = THREE_BYTE_INT(buf);
      pMem->flags = MEM_Int;
      testcase( pMem->u.i<0 );
      return 3;
    }
    case 4: {


      pMem->u.i = FOUR_BYTE_INT(buf);
#ifdef __HP_cc

      if( buf[0]&0x80 ) pMem->u.i |= 0xffffffff80000000LL;
#endif
      pMem->flags = MEM_Int;
      testcase( pMem->u.i<0 );
      return 4;
    }
    case 5: {


      pMem->u.i = FOUR_BYTE_UINT(buf+2) + (((i64)1)<<32)*TWO_BYTE_INT(buf);
      pMem->flags = MEM_Int;
      testcase( pMem->u.i<0 );
      return 6;
    }
    case 6:
    case 7: {


      return serialGet(buf,serial_type,pMem);
    }
    case 8:
    case 9: {


      pMem->u.i = serial_type-8;
      pMem->flags = MEM_Int;
      return 0;
    }
    default: {


      static const u16 aFlag[] = { MEM_Blob|MEM_Ephem, MEM_Str|MEM_Ephem };
      pMem->z = (char *)buf;
      pMem->n = (serial_type-12)/2;
      pMem->flags = aFlag[serial_type&1];
      return pMem->n;
    }
  }
  return 0;
}
