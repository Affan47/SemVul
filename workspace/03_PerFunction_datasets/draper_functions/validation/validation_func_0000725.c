handleTransliterate(Replaceable& text, UTransPosition& pos,
                                                 UBool isIncremental) const {
    int32_t start = pos.start;
    int32_t limit = pos.limit;
    int32_t i, j, ipat;

    while (start < limit) {


        for (j=0, ipat=0; spec[ipat] != END; ++j) {


            int32_t prefixLen = spec[ipat++];
            int32_t suffixLen = spec[ipat++];
            int8_t  radix     = (int8_t) spec[ipat++];
            int32_t minDigits = spec[ipat++];
            int32_t maxDigits = spec[ipat++];


            int32_t s = start;
            UBool match = TRUE;

            for (i=0; i<prefixLen; ++i) {
                if (s >= limit) {
                    if (i > 0) {


                        if (isIncremental) {
                            goto exit;
                        }
                        match = FALSE;
                        break;
                    }
                }
                UChar c = text.charAt(s++);
                if (c != spec[ipat + i]) {
                    match = FALSE;
                    break;
                }
            }

            if (match) {
                UChar32 u = 0;
                int32_t digitCount = 0;
                for (;;) {
                    if (s >= limit) {

                        if (s > start && isIncremental) {
                            goto exit;
                        }
                        break;
                    }
                    UChar32 ch = text.char32At(s);
                    int32_t digit = u_digit(ch, radix);
                    if (digit < 0) {
                        break;
                    }
                    s += U16_LENGTH(ch);
                    u = (u * radix) + digit;
                    if (++digitCount == maxDigits) {
                        break;
                    }
                }

                match = (digitCount >= minDigits);

                if (match) {
                    for (i=0; i<suffixLen; ++i) {
                        if (s >= limit) {

                            if (s > start && isIncremental) {
                                goto exit;
                            }
                            match = FALSE;
                            break;
                        }
                        UChar c = text.charAt(s++);
                        if (c != spec[ipat + prefixLen + i]) {
                            match = FALSE;
                            break;
                        }
                    }

                    if (match) {

                        UnicodeString str(u);
                        text.handleReplaceBetween(start, s, str);
                        limit -= s - start - str.length();


                        break;
                    }
                }
            }

            ipat += prefixLen + suffixLen;
        }

        if (start < limit) {
            start += U16_LENGTH(text.char32At(start));
        }
    }

  exit:
    pos.contextLimit += limit - pos.limit;
    pos.limit = limit;
    pos.start = start;
}
