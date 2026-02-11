CompressSequence ( str  sequence,
                                  UINT length )

{
    str compressed = NULL;

    if (sequence && length)
    {
        str tmp = new char [length + 1];

        if (tmp)
        {
            str ptr = tmp;

            while (*sequence)
            {
                switch (BIndex[safeCharIndex(*sequence)])
                {
                    case ADENIN:
                    case CYTOSIN:
                    case GUANIN:
                    case URACIL:
                    case ONE:
                    {
                        *ptr++ = *sequence;
                        break;
                    }
                    case ANY:
                    {

                        if ((ptr == tmp) ||
                            ((ptr > tmp) &&
                             (BIndex[safeCharIndex(*(ptr - 1))] != ANY))) *ptr++ = *sequence;

                        while(*sequence &&
                              BIndex[safeCharIndex(*sequence)] == ANY) sequence++;

                        sequence--;
                        break;
                    }
                    case INSERT:    break;
                    case INVALID:
                    default:
                    {
                        *ptr++ = BCharacter[ONE];
                        break;
                    }
                }

                sequence++;
            }

            *ptr = 0;

            compressed = strdup(tmp);

            delete tmp;
        }
    }

    return compressed;
}
