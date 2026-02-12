std::string PngChunk::makeAsciiTxtChunk(const std::string& keyword, const std::string& text, bool compress)
        {


            std::string chunkData = keyword + '\0';
            std::string chunkType;
            if (compress) {
                chunkData += '\0' + zlibCompress(text);
                chunkType = "zTXt";
            } else {
                chunkData += text;
                chunkType = "tEXt";
            }

            byte length[4];
            ul2Data(length, static_cast<uint32_t>(chunkData.size()), bigEndian);

            std::string crcData = chunkType + chunkData;
            uLong tmp = crc32(0L, Z_NULL, 0);
            tmp = crc32(tmp, (const Bytef*)crcData.data(), static_cast<uInt>(crcData.size()));
            byte crc[4];
            ul2Data(crc, tmp, bigEndian);

            return std::string((const char*)length, 4) + chunkType + chunkData + std::string((const char*)crc, 4);

        }
