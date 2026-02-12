void TiffDecoder::decodeTiffEntry(const TiffEntryBase* object)
    {
        assert(object != 0);


        if (!object->pValue()) return;

        const DecoderFct decoderFct = findDecoderFct_(make_,
                                                      object->tag(),
                                                      object->group());

        if (decoderFct) {
            EXV_CALL_MEMBER_FN(*this, decoderFct)(object);
        }
    }
