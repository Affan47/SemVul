defineSymbol( char *name, WORD32 val, SYMTYP type, WORD32 start )
{
  SYM_T  *sym;
  WORD32  xref_count;

  if( strlen( name ) < 1 )
  {
    return( &sym_undefined );
  }
  sym = lookup( name );
  xref_count = 0;

  if( M_DEFINED( sym->type ) && sym->val != val && M_NOTRDEF( sym -> type ))
  {
    if( pass == 2 )
    {
      errorSymbol( &redefined_symbol, sym->name, start );
      type = type | REDEFINED;
      sym->xref_count++;
      xref_count = sym->xref_count;
    }
  return ( sym );
  }
  if( M_FIXED( sym->type ))
  {
  return ( sym );
  }

  if( pass == 2 && xref )
  {


    xreftab[sym->xref_index] = lineno;

    xreftab[sym->xref_index + xref_count] = lineno;
  }


  sym->val = ( type == LABEL) ? val : val & 07777;
  sym->type = ( pass == 1 ) ? ( type | CONDITION ) : type;
  return( sym );
}
