DataBuf PngChunk::parseTXTChunk(const DataBuf& data,
                                    int            keysize,
                                    TxtChunkType   type)
    {
        DataBuf arr;

        if(type == zTXt_Chunk)
        {


            const byte* compressionMethod = data.pData_ + keysize + 1;
            if ( *compressionMethod != 0x00 )
            {

#ifdef DEBUG
                std::cerr << "Exiv2::PngChunk::parseTXTChunk: Non-standard zTXt compression method.\n";
#endif
                throw Error(kerFailedToReadImageData);
            }


            const byte* compressedText      = data.pData_ + keysize + 2;
            unsigned int compressedTextSize = data.size_  - keysize - 2;

            zlibUncompress(compressedText, compressedTextSize, arr);
        }
        else if(type == tEXt_Chunk)
        {


            const byte* text = data.pData_ + keysize + 1;
            long textsize    = data.size_  - keysize - 1;

            arr = DataBuf(text, textsize);
        }
        else if(type == iTXt_Chunk)
        {
            const int nullSeparators = std::count(&data.pData_[keysize+3], &data.pData_[data.size_], '\0');
            enforce(nullSeparators >= 2, Exiv2::kerCorruptedMetadata);


            const byte compressionFlag   = data.pData_[keysize + 1];

            const byte compressionMethod = data.pData_[keysize + 2];

            enforce(compressionFlag == 0x00 || compressionFlag == 0x01, Exiv2::kerCorruptedMetadata);
            enforce(compressionMethod == 0x00, Exiv2::kerCorruptedMetadata);


            std::string languageText((const char*)(data.pData_ + keysize + 3));
            unsigned int languageTextSize = static_cast<unsigned int>(languageText.size());

            std::string translatedKeyText((const char*)(data.pData_ + keysize + 3 + languageTextSize +1));
            unsigned int translatedKeyTextSize = static_cast<unsigned int>(translatedKeyText.size());

            if ( compressionFlag == 0x00 )
            {

#ifdef DEBUG
                std::cout << "Exiv2::PngChunk::parseTXTChunk: We found an uncompressed iTXt field\n";
#endif


                const byte* text = data.pData_ + keysize + 3 + languageTextSize + 1 + translatedKeyTextSize + 1;
                long textsize    = data.size_ - (keysize + 3 + languageTextSize + 1 + translatedKeyTextSize + 1);

                arr.alloc(textsize);
                arr = DataBuf(text, textsize);
            }
            else if ( compressionFlag == 0x01 && compressionMethod == 0x00 )
            {

#ifdef DEBUG
                std::cout << "Exiv2::PngChunk::parseTXTChunk: We found a zlib compressed iTXt field\n";
#endif


                const byte* compressedText = data.pData_ + keysize + 3 + languageTextSize + 1 + translatedKeyTextSize + 1;
                long compressedTextSize    = data.size_ - (keysize + 3 + languageTextSize + 1 + translatedKeyTextSize + 1);

                zlibUncompress(compressedText, compressedTextSize, arr);
            }
            else
            {

#ifdef DEBUG
                std::cerr << "Exiv2::PngChunk::parseTXTChunk: Non-standard iTXt compression method.\n";
#endif
                throw Error(kerFailedToReadImageData);
            }
        }
        else
        {
#ifdef DEBUG
            std::cerr << "Exiv2::PngChunk::parseTXTChunk: We found a field, not expected though\n";
#endif
            throw Error(kerFailedToReadImageData);
        }

        return arr;

    }
