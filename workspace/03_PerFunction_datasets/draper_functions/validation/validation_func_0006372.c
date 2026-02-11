getCodecDesc() const
    {
        CodecDesc desc;


        desc.fileType = "PNG";


        desc.pixelTypes.resize(2);
        desc.pixelTypes[0] = "UINT8";
        desc.pixelTypes[1] = "UINT16";


        desc.compressionTypes.resize(1);
        desc.compressionTypes[0] = "LOSSLESS";


        desc.magicStrings.resize(1);
        desc.magicStrings[0].resize(4);
        desc.magicStrings[0][0] = '\x89';
        desc.magicStrings[0][1] = 'P';
        desc.magicStrings[0][2] = 'N';
        desc.magicStrings[0][3] = 'G';


        desc.fileExtensions.resize(1);
        desc.fileExtensions[0] = "png";

        desc.bandNumbers.resize(4);
        desc.bandNumbers[0] = 1;
        desc.bandNumbers[1] = 2;
        desc.bandNumbers[2] = 3;
        desc.bandNumbers[3] = 4;

        return desc;
    }
