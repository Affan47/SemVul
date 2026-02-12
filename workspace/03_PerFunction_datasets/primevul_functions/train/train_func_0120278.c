void WebPImage::doWriteMetadata(BasicIo& outIo)
    {
        if (!io_->isopen()) throw Error(kerInputDataReadFailed);
        if (!outIo.isopen()) throw Error(kerImageWriteFailed);

#ifdef EXIV2_DEBUG_MESSAGES
        std::cout << "Writing metadata" << std::endl;
#endif

        byte    data   [WEBP_TAG_SIZE*3];
        DataBuf chunkId(WEBP_TAG_SIZE+1);
        chunkId.pData_ [WEBP_TAG_SIZE] = '\0';

        readOrThrow(*io_, data, WEBP_TAG_SIZE * 3, Exiv2::kerCorruptedMetadata);
        uint64_t filesize = Exiv2::getULong(data + WEBP_TAG_SIZE, littleEndian);


        if (outIo.write(data, WEBP_TAG_SIZE * 3) != WEBP_TAG_SIZE * 3)
            throw Error(kerImageWriteFailed);


        bool has_size  = false;
        bool has_xmp   = false;
        bool has_exif  = false;
        bool has_vp8x  = false;
        bool has_alpha = false;
        bool has_icc   = iccProfileDefined();

        int width      = 0;
        int height     = 0;

        byte       size_buff[WEBP_TAG_SIZE];
        Blob       blob;

        if (exifData_.count() > 0) {
            ExifParser::encode(blob, littleEndian, exifData_);
            if (blob.size() > 0) {
                has_exif = true;
            }
        }

        if (xmpData_.count() > 0 && !writeXmpFromPacket()) {
            XmpParser::encode(xmpPacket_, xmpData_,
                              XmpParser::useCompactFormat |
                              XmpParser::omitAllFormatting);
        }
        has_xmp = xmpPacket_.size() > 0;
        std::string xmp(xmpPacket_);


        while ( !io_->eof() && (uint64_t) io_->tell() < filesize) {
            readOrThrow(*io_, chunkId.pData_, WEBP_TAG_SIZE, Exiv2::kerCorruptedMetadata);
            readOrThrow(*io_, size_buff, WEBP_TAG_SIZE, Exiv2::kerCorruptedMetadata);
            const uint32_t size_u32 = Exiv2::getULong(size_buff, littleEndian);


            enforce(size_u32 <= static_cast<size_t>(std::numeric_limits<unsigned int>::max()),
                    Exiv2::kerCorruptedMetadata);
            const long size = static_cast<long>(size_u32);
            DataBuf payload(size);
            readOrThrow(*io_, payload.pData_, payload.size_, Exiv2::kerCorruptedMetadata);
            if ( payload.size_ % 2 ) {
              byte c;
              readOrThrow(*io_, &c, 1, Exiv2::kerCorruptedMetadata);
            }


            if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_VP8X) && !has_vp8x) {
                has_vp8x = true;
            }
            if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_VP8X) && !has_size) {
                enforce(size >= 10, Exiv2::kerCorruptedMetadata);
                has_size = true;
                byte size_buf[WEBP_TAG_SIZE];


                memcpy(&size_buf, &payload.pData_[4], 3);
                size_buf[3] = 0;
                width = Exiv2::getULong(size_buf, littleEndian) + 1;


                memcpy(&size_buf, &payload.pData_[7], 3);
                size_buf[3] = 0;
                height = Exiv2::getULong(size_buf, littleEndian) + 1;
            }


#ifdef __CHECK_FOR_ALPHA__
            if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_ANIM) && !has_alpha) {
                has_alpha = true;
            }
#endif


#ifdef __CHECK_FOR_ALPHA__
            if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_VP8) && !has_alpha) {
                has_alpha = true;
            }
#endif
            if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_VP8) && !has_size) {
                enforce(size >= 10, Exiv2::kerCorruptedMetadata);
                has_size = true;
                byte size_buf[2];


                memcpy(&size_buf, &payload.pData_[6], 2);
                width = Exiv2::getUShort(size_buf, littleEndian) & 0x3fff;


                memcpy(&size_buf, &payload.pData_[8], 2);
                height = Exiv2::getUShort(size_buf, littleEndian) & 0x3fff;
            }


            if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_VP8L) && !has_alpha) {
                enforce(size >= 5, Exiv2::kerCorruptedMetadata);
                if ((payload.pData_[4] & WEBP_VP8X_ALPHA_BIT) == WEBP_VP8X_ALPHA_BIT) {
                    has_alpha = true;
                }
            }
            if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_VP8L) && !has_size) {
                enforce(size >= 5, Exiv2::kerCorruptedMetadata);
                has_size = true;
                byte size_buf_w[2];
                byte size_buf_h[3];


                memcpy(&size_buf_w, &payload.pData_[1], 2);
                size_buf_w[1] &= 0x3F;
                width = Exiv2::getUShort(size_buf_w, littleEndian) + 1;


                memcpy(&size_buf_h, &payload.pData_[2], 3);
                size_buf_h[0] =
                  ((size_buf_h[0] >> 6) & 0x3) |
                    ((size_buf_h[1] & 0x3F) << 0x2);
                size_buf_h[1] =
                  ((size_buf_h[1] >> 6) & 0x3) |
                    ((size_buf_h[2] & 0xF) << 0x2);
                height = Exiv2::getUShort(size_buf_h, littleEndian) + 1;
            }


            if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_ANMF) && !has_alpha) {
                enforce(size >= 6, Exiv2::kerCorruptedMetadata);
                if ((payload.pData_[5] & 0x2) == 0x2) {
                    has_alpha = true;
                }
            }
            if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_ANMF) && !has_size) {
                enforce(size >= 12, Exiv2::kerCorruptedMetadata);
                has_size = true;
                byte size_buf[WEBP_TAG_SIZE];


                memcpy(&size_buf, &payload.pData_[6], 3);
                size_buf[3] = 0;
                width = Exiv2::getULong(size_buf, littleEndian) + 1;


                memcpy(&size_buf, &payload.pData_[9], 3);
                size_buf[3] = 0;
                height = Exiv2::getULong(size_buf, littleEndian) + 1;
            }


            if (equalsWebPTag(chunkId, "ALPH") && !has_alpha) {
                has_alpha = true;
            }
        }


        if (!has_vp8x) {
            inject_VP8X(outIo, has_xmp, has_exif, has_alpha,
                        has_icc, width, height);
        }

        io_->seek(12, BasicIo::beg);
        while ( !io_->eof() && (uint64_t) io_->tell() < filesize) {
            readOrThrow(*io_, chunkId.pData_, 4, Exiv2::kerCorruptedMetadata);
            readOrThrow(*io_, size_buff, 4, Exiv2::kerCorruptedMetadata);

            const uint32_t size_u32 = Exiv2::getULong(size_buff, littleEndian);


            enforce(size_u32 <= static_cast<size_t>(std::numeric_limits<unsigned int>::max()),
                    Exiv2::kerCorruptedMetadata);
            const long size = static_cast<long>(size_u32);

            DataBuf payload(size);
            readOrThrow(*io_, payload.pData_, size, Exiv2::kerCorruptedMetadata);
            if ( io_->tell() % 2 ) io_->seek(+1,BasicIo::cur);

            if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_VP8X)) {
                enforce(size >= 1, Exiv2::kerCorruptedMetadata);
                if (has_icc){
                    payload.pData_[0] |= WEBP_VP8X_ICC_BIT;
                } else {
                    payload.pData_[0] &= ~WEBP_VP8X_ICC_BIT;
                }

                if (has_xmp){
                    payload.pData_[0] |= WEBP_VP8X_XMP_BIT;
                } else {
                    payload.pData_[0] &= ~WEBP_VP8X_XMP_BIT;
                }

                if (has_exif) {
                    payload.pData_[0] |= WEBP_VP8X_EXIF_BIT;
                } else {
                    payload.pData_[0] &= ~WEBP_VP8X_EXIF_BIT;
                }

                if (outIo.write(chunkId.pData_, WEBP_TAG_SIZE) != WEBP_TAG_SIZE)
                    throw Error(kerImageWriteFailed);
                if (outIo.write(size_buff, WEBP_TAG_SIZE) != WEBP_TAG_SIZE)
                    throw Error(kerImageWriteFailed);
                if (outIo.write(payload.pData_, payload.size_) != payload.size_)
                    throw Error(kerImageWriteFailed);
                if (outIo.tell() % 2) {
                    if (outIo.write(&WEBP_PAD_ODD, 1) != 1) throw Error(kerImageWriteFailed);
                }

                if (has_icc) {
                    if (outIo.write((const byte*)WEBP_CHUNK_HEADER_ICCP, WEBP_TAG_SIZE) != WEBP_TAG_SIZE) throw Error(kerImageWriteFailed);
                    ul2Data(data, (uint32_t) iccProfile_.size_, littleEndian);
                    if (outIo.write(data, WEBP_TAG_SIZE) != WEBP_TAG_SIZE) throw Error(kerImageWriteFailed);
                    if (outIo.write(iccProfile_.pData_, iccProfile_.size_) != iccProfile_.size_) {
                        throw Error(kerImageWriteFailed);
                    }
                    has_icc = false;
                }
            } else if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_ICCP)) {

            } else if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_EXIF)) {

            } else if (equalsWebPTag(chunkId, WEBP_CHUNK_HEADER_XMP)) {

            } else {
                if (outIo.write(chunkId.pData_, WEBP_TAG_SIZE) != WEBP_TAG_SIZE)
                    throw Error(kerImageWriteFailed);
                if (outIo.write(size_buff, WEBP_TAG_SIZE) != WEBP_TAG_SIZE)
                    throw Error(kerImageWriteFailed);
                if (outIo.write(payload.pData_, payload.size_) != payload.size_)
                    throw Error(kerImageWriteFailed);
            }


            if (outIo.tell() % 2) {
                if (outIo.write(&WEBP_PAD_ODD, 1) != 1) throw Error(kerImageWriteFailed);
            }
        }

        if (has_exif) {
            if (outIo.write((const byte*)WEBP_CHUNK_HEADER_EXIF, WEBP_TAG_SIZE) != WEBP_TAG_SIZE) throw Error(kerImageWriteFailed);
            us2Data(data, (uint16_t) blob.size()+8, bigEndian);
            ul2Data(data, (uint32_t) blob.size(), littleEndian);
            if (outIo.write(data, WEBP_TAG_SIZE) != WEBP_TAG_SIZE) throw Error(kerImageWriteFailed);
            if (outIo.write((const byte*)&blob[0], static_cast<long>(blob.size())) != (long)blob.size())
            {
                throw Error(kerImageWriteFailed);
            }
            if (outIo.tell() % 2) {
                if (outIo.write(&WEBP_PAD_ODD, 1) != 1) throw Error(kerImageWriteFailed);
            }
        }

        if (has_xmp) {
            if (outIo.write((const byte*)WEBP_CHUNK_HEADER_XMP, WEBP_TAG_SIZE) != WEBP_TAG_SIZE) throw Error(kerImageWriteFailed);
            ul2Data(data, (uint32_t) xmpPacket().size(), littleEndian);
            if (outIo.write(data, WEBP_TAG_SIZE) != WEBP_TAG_SIZE) throw Error(kerImageWriteFailed);
            if (outIo.write((const byte*)xmp.data(), static_cast<long>(xmp.size())) != (long)xmp.size()) {
                throw Error(kerImageWriteFailed);
            }
            if (outIo.tell() % 2) {
                if (outIo.write(&WEBP_PAD_ODD, 1) != 1) throw Error(kerImageWriteFailed);
            }
        }


        outIo.seek(0, BasicIo::beg);
        filesize = outIo.size() - 8;
        outIo.seek(4, BasicIo::beg);
        ul2Data(data, (uint32_t) filesize, littleEndian);
        if (outIo.write(data, WEBP_TAG_SIZE) != WEBP_TAG_SIZE) throw Error(kerImageWriteFailed);

    }
