EbmlElement *EbmlElement::CreateElementUsingContext(const EbmlId & aID, const EbmlSemanticContext & Context,
                                                    int & LowLevel, bool IsGlobalContext, bool bAllowDummy, unsigned int MaxLowerLevel)
{
  unsigned int ContextIndex;
  EbmlElement *Result = NULL;


  for (ContextIndex = 0; ContextIndex < EBML_CTX_SIZE(Context); ContextIndex++) {
    if (aID == EBML_CTX_IDX_ID(Context,ContextIndex)) {
      return &EBML_SEM_CREATE(EBML_CTX_IDX(Context,ContextIndex));
    }
  }


  assert(Context.GetGlobalContext != NULL);
  const EbmlSemanticContext & tstContext = Context.GetGlobalContext();
  if (tstContext != Context) {
    LowLevel--;
    MaxLowerLevel--;

    Result = CreateElementUsingContext(aID, tstContext, LowLevel, true, bAllowDummy, MaxLowerLevel);
    if (Result != NULL) {
      return Result;
    }
    LowLevel++;
    MaxLowerLevel++;
  } else {
    return NULL;
  }


  if (EBML_CTX_MASTER(Context) != NULL && aID == EBML_INFO_ID(*EBML_CTX_MASTER(Context))) {
    LowLevel++;
    return &EBML_INFO_CREATE(*EBML_CTX_MASTER(Context));
  }


  if (EBML_CTX_PARENT(Context) != NULL) {
    LowLevel++;
    MaxLowerLevel++;
    return CreateElementUsingContext(aID, *EBML_CTX_PARENT(Context), LowLevel, IsGlobalContext, bAllowDummy, MaxLowerLevel);
  }

  if (!IsGlobalContext && bAllowDummy) {
    LowLevel = 0;
    Result = new (std::nothrow) EbmlDummy(aID);
  }

  return Result;
}
