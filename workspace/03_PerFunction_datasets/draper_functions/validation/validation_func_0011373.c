Lookup_ChainContextSubst( HB_GSUBHeader*    gsub,
					   HB_GSUB_SubTable* st,
					   HB_Buffer         buffer,
					   HB_UShort          flags,
					   HB_UShort          context_length,
					   int                nesting_level )
{
  HB_ChainContextSubst*  ccs = &st->chain;

  switch ( ccs->SubstFormat ) {
    case 1:  return Lookup_ChainContextSubst1( gsub, &ccs->ccsf.ccsf1, buffer, flags, context_length, nesting_level );
    case 2:  return Lookup_ChainContextSubst2( gsub, &ccs->ccsf.ccsf2, buffer, flags, context_length, nesting_level );
    case 3:  return Lookup_ChainContextSubst3( gsub, &ccs->ccsf.ccsf3, buffer, flags, context_length, nesting_level );
    default: return ERR(HB_Err_Invalid_SubTable_Format);
  }
}
