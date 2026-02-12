fribidi_get_par_embedding_levels (

  const FriBidiCharType *bidi_types,
  const FriBidiStrIndex len,

  FriBidiParType *pbase_dir,

  FriBidiLevel *embedding_levels
)
{
  return fribidi_get_par_embedding_levels_ex (
                                              bidi_types,
                                              NULL,
                                              len,

                                              pbase_dir,

                                              embedding_levels);
}
