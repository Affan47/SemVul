void Jp2Image::doWriteMetadata(BasicIo& outIo)
    {
        if (!io_->isopen()) throw Error(kerInputDataReadFailed);
        if (!outIo.isopen()) throw Error(kerImageWriteFailed);

#ifdef EXIV2_DEBUG_MESSAGES
        std::cout << "Exiv2::Jp2Image::doWriteMetadata: Writing JPEG-2000 file " << io_->path() << std::endl;
        std::cout << "Exiv2::Jp2Image::doWriteMetadata: tmp file created " << outIo.path() << std::endl;
#endif


        if (!isJp2Type(*io_, true))
        {
            if (io_->error() || io_->eof()) throw Error(kerInputDataReadFailed);
            throw Error(kerNoImageInInputData);
        }


        if (outIo.write(Jp2Signature, 12) != 12) throw Error(kerImageWriteFailed);

        Jp2BoxHeader box = {0,0};

        byte    boxDataSize[4];
        byte    boxUUIDtype[4];
        DataBuf bheaderBuf(8);


        while(io_->tell() < (long) io_->size())
        {
#ifdef EXIV2_DEBUG_MESSAGES
            std::cout << "Exiv2::Jp2Image::doWriteMetadata: Position: " << io_->tell() << " / " << io_->size() << std::endl;
#endif


            std::memset(bheaderBuf.pData_, 0x00, bheaderBuf.size_);
            long bufRead = io_->read(bheaderBuf.pData_, bheaderBuf.size_);
            if (io_->error()) throw Error(kerFailedToReadImageData);
            if (bufRead != bheaderBuf.size_) throw Error(kerInputDataReadFailed);


            box.length = getLong(bheaderBuf.pData_,     bigEndian);
            box.type   = getLong(bheaderBuf.pData_ + 4, bigEndian);

#ifdef EXIV2_DEBUG_MESSAGES
            std::cout << "Exiv2::Jp2Image::doWriteMetadata: box type: " << toAscii(box.type)
                      << " length: " << box.length << std::endl;
#endif

            if (box.length == 0)
            {
#ifdef EXIV2_DEBUG_MESSAGES
                std::cout << "Exiv2::Jp2Image::doWriteMetadata: Null Box size has been found. "
                             "This is the last box of file." << std::endl;
#endif
                box.length = (uint32_t) (io_->size() - io_->tell() + 8);
            }
            if (box.length < 8)
            {

                throw Error(kerCorruptedMetadata);
            }


            DataBuf boxBuf(box.length);
            memcpy(boxBuf.pData_, bheaderBuf.pData_, 8);
            bufRead = io_->read(boxBuf.pData_ + 8, box.length - 8);
            if (io_->error())
            {
#ifdef EXIV2_DEBUG_MESSAGES
                std::cout << "Exiv2::Jp2Image::doWriteMetadata: Error reading source file" << std::endl;
#endif

                throw Error(kerFailedToReadImageData);
            }

            if (bufRead != (long)(box.length - 8))
            {
#ifdef EXIV2_DEBUG_MESSAGES
                std::cout << "Exiv2::Jp2Image::doWriteMetadata: Cannot read source file data" << std::endl;
#endif
                throw Error(kerInputDataReadFailed);
            }

            switch(box.type)
            {
                case kJp2BoxTypeJp2Header:
                {
                    DataBuf newBuf;
                    encodeJp2Header(boxBuf,newBuf);
#ifdef EXIV2_DEBUG_MESSAGES
                    std::cout << "Exiv2::Jp2Image::doWriteMetadata: Write JP2Header box (length: " << box.length << ")" << std::endl;
#endif
                    if (outIo.write(newBuf.pData_, newBuf.size_) != newBuf.size_) throw Error(kerImageWriteFailed);


                    if (exifData_.count() > 0)
                    {


                        Blob blob;
                        ExifParser::encode(blob, littleEndian, exifData_);
                        if (blob.size())
                        {
                            DataBuf rawExif(static_cast<long>(blob.size()));
                            memcpy(rawExif.pData_, &blob[0], blob.size());

                            DataBuf boxData(8 + 16 + rawExif.size_);
                            ul2Data(boxDataSize, boxData.size_, Exiv2::bigEndian);
                            ul2Data(boxUUIDtype, kJp2BoxTypeUuid, Exiv2::bigEndian);
                            memcpy(boxData.pData_,          boxDataSize,    4);
                            memcpy(boxData.pData_ + 4,      boxUUIDtype,    4);
                            memcpy(boxData.pData_ + 8,      kJp2UuidExif,   16);
                            memcpy(boxData.pData_ + 8 + 16, rawExif.pData_, rawExif.size_);

#ifdef EXIV2_DEBUG_MESSAGES
                            std::cout << "Exiv2::Jp2Image::doWriteMetadata: Write box with Exif metadata (length: "
                                      << boxData.size_ << std::endl;
#endif
                            if (outIo.write(boxData.pData_, boxData.size_) != boxData.size_) throw Error(kerImageWriteFailed);
                        }
                    }

                    if (iptcData_.count() > 0)
                    {


                        DataBuf rawIptc = IptcParser::encode(iptcData_);
                        if (rawIptc.size_ > 0)
                        {
                            DataBuf boxData(8 + 16 + rawIptc.size_);
                            ul2Data(boxDataSize, boxData.size_, Exiv2::bigEndian);
                            ul2Data(boxUUIDtype, kJp2BoxTypeUuid, Exiv2::bigEndian);
                            memcpy(boxData.pData_,          boxDataSize,    4);
                            memcpy(boxData.pData_ + 4,      boxUUIDtype,    4);
                            memcpy(boxData.pData_ + 8,      kJp2UuidIptc,   16);
                            memcpy(boxData.pData_ + 8 + 16, rawIptc.pData_, rawIptc.size_);

#ifdef EXIV2_DEBUG_MESSAGES
                            std::cout << "Exiv2::Jp2Image::doWriteMetadata: Write box with Iptc metadata (length: "
                                      << boxData.size_ << std::endl;
#endif
                            if (outIo.write(boxData.pData_, boxData.size_) != boxData.size_) throw Error(kerImageWriteFailed);
                        }
                    }

                    if (writeXmpFromPacket() == false)
                    {
                        if (XmpParser::encode(xmpPacket_, xmpData_) > 1)
                        {
#ifndef SUPPRESS_WARNINGS
                            EXV_ERROR << "Failed to encode XMP metadata." << std::endl;
#endif
                        }
                    }
                    if (xmpPacket_.size() > 0)
                    {


                        DataBuf xmp(reinterpret_cast<const byte*>(xmpPacket_.data()), static_cast<long>(xmpPacket_.size()));
                        DataBuf boxData(8 + 16 + xmp.size_);
                        ul2Data(boxDataSize, boxData.size_, Exiv2::bigEndian);
                        ul2Data(boxUUIDtype, kJp2BoxTypeUuid, Exiv2::bigEndian);
                        memcpy(boxData.pData_,          boxDataSize,  4);
                        memcpy(boxData.pData_ + 4,      boxUUIDtype,  4);
                        memcpy(boxData.pData_ + 8,      kJp2UuidXmp,  16);
                        memcpy(boxData.pData_ + 8 + 16, xmp.pData_,   xmp.size_);

#ifdef EXIV2_DEBUG_MESSAGES
                        std::cout << "Exiv2::Jp2Image::doWriteMetadata: Write box with XMP metadata (length: "
                                  << boxData.size_ << ")" << std::endl;
#endif
                        if (outIo.write(boxData.pData_, boxData.size_) != boxData.size_) throw Error(kerImageWriteFailed);
                    }

                    break;
                }

                case kJp2BoxTypeUuid:
                {
                    if(memcmp(boxBuf.pData_ + 8, kJp2UuidExif, 16) == 0)
                    {
#ifdef EXIV2_DEBUG_MESSAGES
                        std::cout << "Exiv2::Jp2Image::doWriteMetadata: strip Exif Uuid box" << std::endl;
#endif
                    }
                    else if(memcmp(boxBuf.pData_ + 8, kJp2UuidIptc, 16) == 0)
                    {
#ifdef EXIV2_DEBUG_MESSAGES
                        std::cout << "Exiv2::Jp2Image::doWriteMetadata: strip Iptc Uuid box" << std::endl;
#endif
                    }
                    else if(memcmp(boxBuf.pData_ + 8, kJp2UuidXmp,  16) == 0)
                    {
#ifdef EXIV2_DEBUG_MESSAGES
                        std::cout << "Exiv2::Jp2Image::doWriteMetadata: strip Xmp Uuid box" << std::endl;
#endif
                    }
                    else
                    {
#ifdef EXIV2_DEBUG_MESSAGES
                        std::cout << "Exiv2::Jp2Image::doWriteMetadata: write Uuid box (length: " << box.length << ")" << std::endl;
#endif
                        if (outIo.write(boxBuf.pData_, boxBuf.size_) != boxBuf.size_) throw Error(kerImageWriteFailed);
                    }
                    break;
                }

                default:
                {
#ifdef EXIV2_DEBUG_MESSAGES
                    std::cout << "Exiv2::Jp2Image::doWriteMetadata: write box (length: " << box.length << ")" << std::endl;
#endif
                    if (outIo.write(boxBuf.pData_, boxBuf.size_) != boxBuf.size_) throw Error(kerImageWriteFailed);

                    break;
                }
            }
        }

#ifdef EXIV2_DEBUG_MESSAGES
        std::cout << "Exiv2::Jp2Image::doWriteMetadata: EOF" << std::endl;
#endif

    }
