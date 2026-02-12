void CrwParser::decode(CrwImage* pCrwImage, const byte* pData, uint32_t size)
    {
        assert(pCrwImage != 0);
        assert(pData != 0);


        CiffHeader::UniquePtr head(new CiffHeader);
        head->read(pData, size);
#ifdef DEBUG
        head->print(std::cerr);
#endif
        head->decode(*pCrwImage);


        CiffComponent* preview = head->findComponent(0x2007, 0x0000);
        if (preview) {
            (pCrwImage->exifData())["Exif.Image2.JPEGInterchangeFormat"] = uint32_t(preview->pData() - pData);
            (pCrwImage->exifData())["Exif.Image2.JPEGInterchangeFormatLength"] = preview->size();
        }
    }
