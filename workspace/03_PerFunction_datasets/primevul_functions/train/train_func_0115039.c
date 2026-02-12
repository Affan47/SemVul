void CrwParser::encode(
              Blob&     blob,
        const byte*     pData,
              uint32_t  size,
        const CrwImage* pCrwImage
    )
    {

        CiffHeader::UniquePtr head(new CiffHeader);
        if (size != 0) {
            head->read(pData, size);
        }


        CrwMap::encode(head.get(), *pCrwImage);
        head->write(blob);

    }
