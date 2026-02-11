addComposition(UChar32 start, UChar32 end, uint32_t value) {
    if(norms[value].mappingType==Norm::ROUND_TRIP) {
        if(start!=end) {
            fprintf(stderr,
                    "gennorm2 error: same round-trip mapping for "
                    "more than 1 code point U+%04lX..U+%04lX\n",
                    (long)start, (long)end);
            exit(U_INVALID_FORMAT_ERROR);
        }
        if(norms[value].cc!=0) {
            fprintf(stderr,
                    "gennorm2 error: "
                    "U+%04lX has a round-trip mapping and ccc!=0, "
                    "not possible in Unicode normalization\n",
                    (long)start);
            exit(U_INVALID_FORMAT_ERROR);
        }

        const UnicodeString &m=*norms[value].mapping;
        UChar32 lead=m.char32At(0);
        UChar32 trail=m.char32At(m.length()-1);
        if(getCC(lead)!=0) {
            fprintf(stderr,
                    "gennorm2 error: "
                    "U+%04lX's round-trip mapping's starter U+%04lX has ccc!=0, "
                    "not possible in Unicode normalization\n",
                    (long)start, (long)lead);
            exit(U_INVALID_FORMAT_ERROR);
        }

        createNorm(trail)->combinesBack=TRUE;

        IcuToolErrorCode errorCode("gennorm2/addComposition()");
        Norm *leadNorm=createNorm(lead);
        UVector32 *compositions=leadNorm->compositions;
        int32_t i;
        if(compositions==NULL) {
            compositions=leadNorm->compositions=new UVector32(errorCode);
            i=0;
        } else {

            int32_t length;
            const CompositionPair *pairs=leadNorm->getCompositionPairs(length);
            for(i=0; i<length; ++i) {
                if(trail==pairs[i].trail) {
                    fprintf(stderr,
                            "gennorm2 error: same round-trip mapping for "
                            "more than 1 code point (e.g., U+%04lX) to U+%04lX + U+%04lX\n",
                            (long)start, (long)lead, (long)trail);
                    exit(U_INVALID_FORMAT_ERROR);
                }
                if(trail<pairs[i].trail) {
                    break;
                }
            }
        }
        compositions->insertElementAt(trail, 2*i, errorCode);
        compositions->insertElementAt(start, 2*i+1, errorCode);
    }
}
