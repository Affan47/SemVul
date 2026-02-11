AllocateByteCode(int type)
  {
    ByteCode *result;

    result = new ByteCode;
    if( !result )
      {
        obErrorLog.ThrowError(__FUNCTION__, "Unable to allocate byte codes for biomolecule residue perception.", obError);
        return (result);
      }
    result->type = type;
    result->eval.next     = NULL;
    result->count.tcond   = NULL;
    result->count.fcond   = NULL;
    result->elem.tcond    = NULL;
    result->elem.fcond    = NULL;
    result->ident.tcond   = NULL;
    result->ident.fcond   = NULL;
    result->local.tcond   = NULL;
    result->local.fcond   = NULL;
    result->assign.atomid = NULL;
    result->assign.bflags = NULL;

    return (result);
  }
