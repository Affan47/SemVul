EbmlElement * EbmlElement::SkipData(EbmlStream & DataStream, const EbmlSemanticContext & Context, EbmlElement * TestReadElt, bool AllowDummyElt)
{
  EbmlElement * Result = NULL;
  if (bSizeIsFinite) {
    assert(TestReadElt == NULL);
    assert(ElementPosition < SizePosition);
    DataStream.I_O().setFilePointer(SizePosition + CodedSizeLength(Size, SizeLength, bSizeIsFinite) + Size, seek_beginning);

  } else {


    bool bEndFound = false;
    while (!bEndFound && Result == NULL) {


      if (TestReadElt == NULL) {
        int bUpperElement = 0;
        Result = DataStream.FindNextElement(Context, bUpperElement, 0xFFFFFFFFL, AllowDummyElt);
      } else {
        Result = TestReadElt;
        TestReadElt = NULL;
      }

      if (Result != NULL) {
        unsigned int EltIndex;

        for (EltIndex = 0; EltIndex < EBML_CTX_SIZE(Context); EltIndex++) {
          if (EbmlId(*Result) == EBML_CTX_IDX_ID(Context,EltIndex)) {

            Result = Result->SkipData(DataStream, EBML_SEM_CONTEXT(EBML_CTX_IDX(Context,EltIndex)), NULL);
            break;
          }
        }

        if (EltIndex >= EBML_CTX_SIZE(Context)) {
          if (EBML_CTX_PARENT(Context) != NULL) {
            Result = SkipData(DataStream, *EBML_CTX_PARENT(Context), Result);
          } else {
            assert(Context.GetGlobalContext != NULL);
            if (Context != Context.GetGlobalContext()) {
              Result = SkipData(DataStream, Context.GetGlobalContext(), Result);
            } else {
              bEndFound = true;
            }
          }
        }
      } else {
        bEndFound = true;
      }
    }
  }
  return Result;
}
