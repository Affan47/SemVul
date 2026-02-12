void PngImage::readMetadata()
    {
#ifdef DEBUG
        std::cerr << "Exiv2::PngImage::readMetadata: Reading PNG file " << io_->path() << std::endl;
#endif
        if (io_->open() != 0) {
            throw Error(kerDataSourceOpenFailed, io_->path(), strError());
        }
        IoCloser closer(*io_);
        if (!isPngType(*io_, true)) {
            throw Error(kerNotAnImage, "PNG");
        }
        clearMetadata();

        const long imgSize = (long)io_->size();
        DataBuf cheaderBuf(8);

        while (!io_->eof()) {
            std::memset(cheaderBuf.pData_, 0x0, cheaderBuf.size_);
            readChunk(cheaderBuf, *io_);


            uint32_t chunkLength = Exiv2::getULong(cheaderBuf.pData_, Exiv2::bigEndian);
            long pos = io_->tell();
            if (pos == -1 || chunkLength > uint32_t(0x7FFFFFFF) || static_cast<long>(chunkLength) > imgSize - pos) {
                throw Exiv2::Error(kerFailedToReadImageData);
            }

            std::string chunkType(reinterpret_cast<char*>(cheaderBuf.pData_) + 4, 4);
#ifdef DEBUG
            std::cout << "Exiv2::PngImage::readMetadata: chunk type: " << chunkType << " length: " << chunkLength
                      << std::endl;
#endif


            if (chunkType == "IEND" || chunkType == "IHDR" || chunkType == "tEXt" || chunkType == "zTXt" ||
                chunkType == "iTXt" || chunkType == "iCCP") {
                DataBuf chunkData(chunkLength);
                readChunk(chunkData, *io_);

                if (chunkType == "IEND") {
                    return;
                } else if (chunkType == "IHDR" && chunkData.size_ >= 8) {
                    Internal::PngImageHeader header;
                    PngChunk::decodeIHDRChunk(chunkData, header);
                    pixelWidth_ = header.width;
                    pixelHeight_ = header.height;

                } else if (chunkType == "tEXt") {
                    PngChunk::decodeTXTChunk(this, chunkData, PngChunk::tEXt_Chunk);
                } else if (chunkType == "zTXt") {
                    PngChunk::decodeTXTChunk(this, chunkData, PngChunk::zTXt_Chunk);
                } else if (chunkType == "iTXt") {
                    PngChunk::decodeTXTChunk(this, chunkData, PngChunk::iTXt_Chunk);
                } else if (chunkType == "iCCP") {

                    uint32_t iccOffset = 0;
                    while (iccOffset < 80 && iccOffset < chunkLength) {
                        if (chunkData.pData_[iccOffset++] == 0x00) {
                            break;
                        }
                    }
                    profileName_ = std::string(reinterpret_cast<char*>(chunkData.pData_), iccOffset - 1);
                    ++iccOffset;

                    zlibToDataBuf(chunkData.pData_ + iccOffset, chunkLength - iccOffset, iccProfile_);
#ifdef DEBUG
                    std::cout << "Exiv2::PngImage::readMetadata: profile name: " << profileName_ << std::endl;
                    std::cout << "Exiv2::PngImage::readMetadata: iccProfile.size_ (uncompressed) : "
                              << iccProfile_.size_ << std::endl;
#endif
                }


                chunkLength = 0;
            }


#ifdef DEBUG
            std::cout << "Exiv2::PngImage::readMetadata: Seek to offset: " << chunkLength + 4 << std::endl;
#endif
            io_->seek(chunkLength + 4, BasicIo::cur);
            if (io_->error() || io_->eof()) {
                throw Error(kerFailedToReadImageData);
            }
        }
    }
