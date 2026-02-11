writeNorm16(UChar32 start, UChar32 end, uint32_t value) {
    if(value!=0) {
        const Norm *p=norms+value;
        int32_t offset=p->offset>>Norm::OFFSET_SHIFT;
        int32_t norm16=0;
        UBool isDecompNo=FALSE;
        UBool isCompNoMaybe=FALSE;
        switch(p->offset&Norm::OFFSET_MASK) {
        case Norm::OFFSET_NONE:

            if(p->combinesBack) {
                norm16=Normalizer2Impl::MIN_NORMAL_MAYBE_YES+p->cc;
                isDecompNo=(UBool)(p->cc!=0);
                isCompNoMaybe=TRUE;
            } else if(p->cc!=0) {
                norm16=Normalizer2Impl::MIN_YES_YES_WITH_CC-1+p->cc;
                isDecompNo=isCompNoMaybe=TRUE;
            }
            break;
        case Norm::OFFSET_MAYBE_YES:
            norm16=indexes[Normalizer2Impl::IX_MIN_MAYBE_YES]+offset;
            isCompNoMaybe=TRUE;
            break;
        case Norm::OFFSET_YES_YES:
            norm16=offset;
            break;
        case Norm::OFFSET_YES_NO_MAPPING_AND_COMPOSITION:
            norm16=indexes[Normalizer2Impl::IX_MIN_YES_NO]+offset;
            isDecompNo=TRUE;
            break;
        case Norm::OFFSET_YES_NO_MAPPING_ONLY:
            norm16=indexes[Normalizer2Impl::IX_MIN_YES_NO_MAPPINGS_ONLY]+offset;
            isDecompNo=TRUE;
            break;
        case Norm::OFFSET_NO_NO:
            norm16=indexes[Normalizer2Impl::IX_MIN_NO_NO]+offset;
            isDecompNo=isCompNoMaybe=TRUE;
            break;
        case Norm::OFFSET_DELTA:
            norm16=getCenterNoNoDelta()+offset;
            isDecompNo=isCompNoMaybe=TRUE;
            break;
        default:
            exit(U_INTERNAL_PROGRAM_ERROR);
        }
        IcuToolErrorCode errorCode("gennorm2/writeNorm16()");
        utrie2_setRange32(norm16Trie, start, end, (uint32_t)norm16, TRUE, errorCode);
        if(isDecompNo && start<indexes[Normalizer2Impl::IX_MIN_DECOMP_NO_CP]) {
            indexes[Normalizer2Impl::IX_MIN_DECOMP_NO_CP]=start;
        }
        if(isCompNoMaybe && start<indexes[Normalizer2Impl::IX_MIN_COMP_NO_MAYBE_CP]) {
            indexes[Normalizer2Impl::IX_MIN_COMP_NO_MAYBE_CP]=start;
        }
    }
}
