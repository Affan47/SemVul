void JpegBase::doWriteMetadata(BasicIo& outIo)
    {
        if (!io_->isopen()) throw Error(20);
        if (!outIo.isopen()) throw Error(21);


        if (!isThisType(*io_, true)) {
            if (io_->error() || io_->eof()) throw Error(20);
            throw Error(22);
        }

        const long bufMinSize = 36;
        long bufRead = 0;
        DataBuf buf(bufMinSize);
        const long seek = io_->tell();
        int count = 0;
        int search = 0;
        int insertPos = 0;
        int comPos = 0;
        int skipApp1Exif = -1;
        int skipApp1Xmp = -1;
        bool foundCompletePsData = false;
        std::vector<int> skipApp13Ps3;
        int skipCom = -1;
        Blob psBlob;
        DataBuf rawExif;


        if (writeHeader(outIo)) throw Error(21);


        int marker = advanceToMarker();
        if (marker < 0) throw Error(22);


        while (marker != sos_ && marker != eoi_ && search < 5) {

            bufRead = io_->read(buf.pData_, bufMinSize);
            if (io_->error()) throw Error(20);
            uint16_t size = getUShort(buf.pData_, bigEndian);

            if (marker == app0_) {
                if (size < 2) throw Error(22);
                insertPos = count + 1;
                if (io_->seek(size-bufRead, BasicIo::cur)) throw Error(22);
            }
            else if (   skipApp1Exif == -1
                     && marker == app1_ && memcmp(buf.pData_ + 2, exifId_, 6) == 0) {
                if (size < 8) throw Error(22);
                skipApp1Exif = count;
                ++search;

                io_->seek(8 - bufRead, BasicIo::cur);
                rawExif.alloc(size - 8);
                io_->read(rawExif.pData_, rawExif.size_);
                if (io_->error() || io_->eof()) throw Error(22);
            }
            else if (   skipApp1Xmp == -1
                     && marker == app1_ && memcmp(buf.pData_ + 2, xmpId_, 29) == 0) {
                if (size < 31) throw Error(22);
                skipApp1Xmp = count;
                ++search;
                if (io_->seek(size-bufRead, BasicIo::cur)) throw Error(22);
            }
            else if (   !foundCompletePsData
                     && marker == app13_ && memcmp(buf.pData_ + 2, Photoshop::ps3Id_, 14) == 0) {
#ifdef DEBUG
                std::cerr << "Found APP13 Photoshop PS3 segment\n";
#endif
                if (size < 16) throw Error(22);
                skipApp13Ps3.push_back(count);
                io_->seek(16 - bufRead, BasicIo::cur);

                DataBuf psData(size - 16);
                io_->read(psData.pData_, size - 16);
                if (io_->error() || io_->eof()) throw Error(20);

                append(psBlob, psData.pData_, psData.size_);

                if (psBlob.size() > 0 && Photoshop::valid(&psBlob[0],(long) psBlob.size())) {
                    foundCompletePsData = true;
                }
            }
            else if (marker == com_ && skipCom == -1) {
                if (size < 2) throw Error(22);


                skipCom = count;
                ++search;
                if (io_->seek(size-bufRead, BasicIo::cur)) throw Error(22);
            }
            else {
                if (size < 2) throw Error(22);
                if (io_->seek(size-bufRead, BasicIo::cur)) throw Error(22);
            }


            if (   comPos == 0
                && (   marker == sof0_
                    || marker == sof1_
                    || marker == sof2_
                    || marker == sof3_
                    || marker == sof5_
                    || marker == sof6_
                    || marker == sof7_
                    || marker == sof9_
                    || marker == sof10_
                    || marker == sof11_
                    || marker == sof13_
                    || marker == sof14_
                    || marker == sof15_)) {
                comPos = count;
                ++search;
            }
            marker = advanceToMarker();
            if (marker < 0) throw Error(22);
            ++count;
        }

        if (!foundCompletePsData && psBlob.size() > 0) throw Error(22);
        search += (int) skipApp13Ps3.size();

        if (comPos == 0) {
            if (marker == eoi_) comPos = count;
            else comPos = insertPos;
            ++search;
        }
        if (exifData_.count() > 0) ++search;
        if (writeXmpFromPacket() == false && xmpData_.count() > 0) ++search;
        if (writeXmpFromPacket() == true && xmpPacket_.size() > 0) ++search;
        if (foundCompletePsData || iptcData_.count() > 0) ++search;
        if (!comment_.empty()) ++search;

        io_->seek(seek, BasicIo::beg);
        count = 0;
        marker = advanceToMarker();
        if (marker < 0) throw Error(22);


        while (marker != sos_ && search > 0) {

            bufRead = io_->read(buf.pData_, bufMinSize);
            if (io_->error()) throw Error(20);


            uint16_t size = getUShort(buf.pData_, bigEndian);

            if (insertPos == count) {
                byte tmpBuf[64];


                if (exifData_.count() > 0) {
                    Blob blob;
                    ByteOrder bo = byteOrder();
                    if (bo == invalidByteOrder) {
                        bo = littleEndian;
                        setByteOrder(bo);
                    }
                    WriteMethod wm = ExifParser::encode(blob,
                                                        rawExif.pData_,
                                                        rawExif.size_,
                                                        bo,
                                                        exifData_);
                    const byte* pExifData = rawExif.pData_;
                    uint32_t exifSize = rawExif.size_;
                    if (wm == wmIntrusive) {
                        pExifData = blob.size() > 0 ? &blob[0] : 0;
                        exifSize = static_cast<uint32_t>(blob.size());
                    }
                    if (exifSize > 0) {

                        tmpBuf[0] = 0xff;
                        tmpBuf[1] = app1_;

                        if (exifSize + 8 > 0xffff) throw Error(37, "Exif");
                        us2Data(tmpBuf + 2, static_cast<uint16_t>(exifSize + 8), bigEndian);
                        std::memcpy(tmpBuf + 4, exifId_, 6);
                        if (outIo.write(tmpBuf, 10) != 10) throw Error(21);


                        if (   outIo.write(pExifData, exifSize)
                            != static_cast<long>(exifSize)) throw Error(21);
                        if (outIo.error()) throw Error(21);
                        --search;
                    }
                }
                if (writeXmpFromPacket() == false) {
                    if (XmpParser::encode(xmpPacket_, xmpData_, XmpParser::useCompactFormat | XmpParser::omitAllFormatting) > 1) {
#ifndef SUPPRESS_WARNINGS
                        EXV_ERROR << "Failed to encode XMP metadata.\n";
#endif
                    }
                }
                if (xmpPacket_.size() > 0) {

                    tmpBuf[0] = 0xff;
                    tmpBuf[1] = app1_;

                    if (xmpPacket_.size() + 31 > 0xffff) throw Error(37, "XMP");
                    us2Data(tmpBuf + 2, static_cast<uint16_t>(xmpPacket_.size() + 31), bigEndian);
                    std::memcpy(tmpBuf + 4, xmpId_, 29);
                    if (outIo.write(tmpBuf, 33) != 33) throw Error(21);


                    if (   outIo.write(reinterpret_cast<const byte*>(xmpPacket_.data()), static_cast<long>(xmpPacket_.size()))
                        != static_cast<long>(xmpPacket_.size())) throw Error(21);
                    if (outIo.error()) throw Error(21);
                    --search;
                }
                if (foundCompletePsData || iptcData_.count() > 0) {


                    DataBuf newPsData = Photoshop::setIptcIrb(psBlob.size() > 0 ? &psBlob[0] : 0,
                                                              (long) psBlob.size(),
                                                              iptcData_);
                    const long maxChunkSize = 0xffff - 16;
                    const byte* chunkStart = newPsData.pData_;
                    const byte* chunkEnd = chunkStart + newPsData.size_;
                    while (chunkStart < chunkEnd) {

                        long chunkSize = static_cast<long>(chunkEnd - chunkStart);
                        if (chunkSize > maxChunkSize) {
                            chunkSize = maxChunkSize;

                            const long writtenSize = static_cast<long>(chunkStart - newPsData.pData_);
                            if (Photoshop::valid(newPsData.pData_, writtenSize + chunkSize)) {


                                chunkSize -= 8;
                            }
                        }


                        tmpBuf[0] = 0xff;
                        tmpBuf[1] = app13_;
                        us2Data(tmpBuf + 2, static_cast<uint16_t>(chunkSize + 16), bigEndian);
                        std::memcpy(tmpBuf + 4, Photoshop::ps3Id_, 14);
                        if (outIo.write(tmpBuf, 18) != 18) throw Error(21);
                        if (outIo.error()) throw Error(21);


                        if (outIo.write(chunkStart, chunkSize) != chunkSize) throw Error(21);
                        if (outIo.error()) throw Error(21);

                        chunkStart += chunkSize;
                    }
                    --search;
                }
            }
            if (comPos == count) {
                if (!comment_.empty()) {
                    byte tmpBuf[4];

                    tmpBuf[0] = 0xff;
                    tmpBuf[1] = com_;

                    if (comment_.length() + 3 > 0xffff) throw Error(37, "JPEG comment");
                    us2Data(tmpBuf + 2, static_cast<uint16_t>(comment_.length() + 3), bigEndian);

                    if (outIo.write(tmpBuf, 4) != 4) throw Error(21);
                    if (outIo.write((byte*)comment_.data(), (long)comment_.length())
                        != (long)comment_.length()) throw Error(21);
                    if (outIo.putb(0)==EOF) throw Error(21);
                    if (outIo.error()) throw Error(21);
                    --search;
                }
                --search;
            }
            if (marker == eoi_) {
                break;
            }
            else if (   skipApp1Exif == count
                     || skipApp1Xmp  == count
                     || std::find(skipApp13Ps3.begin(), skipApp13Ps3.end(), count) != skipApp13Ps3.end()
                     || skipCom      == count) {
                --search;
                io_->seek(size-bufRead, BasicIo::cur);
            }
            else {
                if (size < 2) throw Error(22);
                buf.alloc(size+2);
                io_->seek(-bufRead-2, BasicIo::cur);
                io_->read(buf.pData_, size+2);
                if (io_->error() || io_->eof()) throw Error(20);
                if (outIo.write(buf.pData_, size+2) != size+2) throw Error(21);
                if (outIo.error()) throw Error(21);
            }


            marker = advanceToMarker();
            if (marker < 0) throw Error(22);
            ++count;
        }


        io_->populateFakeData();


        io_->seek(-2, BasicIo::cur);
        buf.alloc(4096);
        long readSize = 0;
        while ((readSize=io_->read(buf.pData_, buf.size_))) {
            if (outIo.write(buf.pData_, readSize) != readSize) throw Error(21);
        }
        if (outIo.error()) throw Error(21);

    }
