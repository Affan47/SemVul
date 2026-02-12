void PsdImage::doWriteMetadata(BasicIo& outIo)
    {
        if (!io_->isopen())
            throw Error(kerInputDataReadFailed);
        if (!outIo.isopen())
            throw Error(kerImageWriteFailed);

#ifdef DEBUG
        std::cout << "Exiv2::PsdImage::doWriteMetadata: Writing PSD file " << io_->path() << "\n";
        std::cout << "Exiv2::PsdImage::doWriteMetadata: tmp file created " << outIo.path() << "\n";
#endif


        if (!isPsdType(*io_, true)) {
            if (io_->error() || io_->eof())
                throw Error(kerInputDataReadFailed);
            throw Error(kerNoImageInInputData);
        }

        io_->seek(0, BasicIo::beg);

        DataBuf lbuf(4096);
        byte buf[8];


        byte psd_head[26];
        if (io_->read(psd_head, 26) != 26)
            throw Error(kerNotAnImage, "Photoshop");


        if (outIo.write(psd_head, 26) != 26)
            throw Error(kerImageWriteFailed);


        if (io_->read(buf, 4) != 4)
            throw Error(kerNotAnImage, "Photoshop");

        uint32_t colorDataLength = getULong(buf, bigEndian);


        ul2Data(buf, colorDataLength, bigEndian);
        if (outIo.write(buf, 4) != 4)
            throw Error(kerImageWriteFailed);
#ifdef DEBUG
        std::cerr << std::dec << "colorDataLength: " << colorDataLength << "\n";
#endif

        size_t readTotal = 0;
        size_t toRead = 0;
        while (readTotal < colorDataLength) {
            toRead = static_cast<size_t>(colorDataLength - readTotal) < lbuf.size_
                         ? static_cast<size_t>(colorDataLength - readTotal)
                         : lbuf.size_;
            if (io_->read(lbuf.pData_, toRead) != toRead)
                throw Error(kerNotAnImage, "Photoshop");
            readTotal += toRead;
            if (outIo.write(lbuf.pData_, toRead) != toRead)
                throw Error(kerImageWriteFailed);
        }
        if (outIo.error())
            throw Error(kerImageWriteFailed);

        uint32_t resLenOffset = io_->tell();


        if (io_->read(buf, 4) != 4)
            throw Error(kerNotAnImage, "Photoshop");

        uint32_t oldResLength = getULong(buf, bigEndian);
        uint32_t newResLength = 0;


        ul2Data(buf, oldResLength, bigEndian);
        if (outIo.write(buf, 4) != 4)
            throw Error(kerImageWriteFailed);

#ifdef DEBUG
        std::cerr << std::dec << "oldResLength: " << oldResLength << "\n";
#endif


        bool iptcDone = false;
        bool exifDone = false;
        bool xmpDone = false;
        while (oldResLength > 0) {
            if (io_->read(buf, 8) != 8)
                throw Error(kerNotAnImage, "Photoshop");


            uint32_t resourceType = getULong(buf, bigEndian);

            if (!Photoshop::isIrb(buf, 4)) {
                throw Error(kerNotAnImage, "Photoshop");
            }
            uint16_t resourceId = getUShort(buf + 4, bigEndian);
            uint32_t resourceNameLength = buf[6];
            uint32_t adjResourceNameLen = resourceNameLength & ~1;
            unsigned char resourceNameFirstChar = buf[7];


            DataBuf resName(256);
            if (io_->read(resName.pData_, adjResourceNameLen) != static_cast<long>(adjResourceNameLen))
                throw Error(kerNotAnImage, "Photoshop");


            if (io_->read(buf, 4) != 4)
                throw Error(kerNotAnImage, "Photoshop");

            uint32_t resourceSize = getULong(buf, bigEndian);
            uint32_t pResourceSize = (resourceSize + 1) & ~1;
            uint32_t curOffset = io_->tell();


            if ((resourceId == kPhotoshopResourceID_IPTC_NAA || resourceId > kPhotoshopResourceID_IPTC_NAA) &&
                iptcDone == false) {
                newResLength += writeIptcData(iptcData_, outIo);
                iptcDone = true;
            }


            else if ((resourceId == kPhotoshopResourceID_ExifInfo || resourceId > kPhotoshopResourceID_ExifInfo) &&
                     exifDone == false) {
                newResLength += writeExifData(exifData_, outIo);
                exifDone = true;
            }


            else if ((resourceId == kPhotoshopResourceID_XMPPacket || resourceId > kPhotoshopResourceID_XMPPacket) &&
                     xmpDone == false) {
                newResLength += writeXmpData(xmpData_, outIo);
                xmpDone = true;
            }


            if (resourceId != kPhotoshopResourceID_IPTC_NAA && resourceId != kPhotoshopResourceID_ExifInfo &&
                resourceId != kPhotoshopResourceID_XMPPacket) {
#ifdef DEBUG
                std::cerr << std::hex << "copy : resourceType: " << resourceType << "\n";
                std::cerr << std::hex << "copy : resourceId: " << resourceId << "\n";
                std::cerr << std::dec;
#endif

                ul2Data(buf, resourceType, bigEndian);
                if (outIo.write(buf, 4) != 4)
                    throw Error(kerImageWriteFailed);
                us2Data(buf, resourceId, bigEndian);
                if (outIo.write(buf, 2) != 2)
                    throw Error(kerImageWriteFailed);

                buf[0] = resourceNameLength & 0x00ff;
                if (outIo.write(buf, 1) != 1)
                    throw Error(kerImageWriteFailed);
                buf[0] = resourceNameFirstChar;
                if (outIo.write(buf, 1) != 1)
                    throw Error(kerImageWriteFailed);
                if (outIo.write(resName.pData_, adjResourceNameLen) != static_cast<long>(adjResourceNameLen))
                    throw Error(kerImageWriteFailed);
                ul2Data(buf, resourceSize, bigEndian);
                if (outIo.write(buf, 4) != 4)
                    throw Error(kerImageWriteFailed);

                readTotal = 0;
                toRead = 0;
                while (readTotal < pResourceSize) {
                    toRead = static_cast<long>(pResourceSize - readTotal) < lbuf.size_
                                 ? static_cast<long>(pResourceSize - readTotal)
                                 : lbuf.size_;
                    if (io_->read(lbuf.pData_, toRead) != toRead) {
                        throw Error(kerNotAnImage, "Photoshop");
                    }
                    readTotal += toRead;
                    if (outIo.write(lbuf.pData_, toRead) != toRead)
                        throw Error(kerImageWriteFailed);
                }
                if (outIo.error())
                    throw Error(kerImageWriteFailed);
                newResLength += pResourceSize + adjResourceNameLen + 12;
            }

            io_->seek(curOffset + pResourceSize, BasicIo::beg);
            oldResLength -= (12 + adjResourceNameLen + pResourceSize);
        }


        if (iptcDone == false) {
            newResLength += writeIptcData(iptcData_, outIo);
        }


        if (exifDone == false) {
            newResLength += writeExifData(exifData_, outIo);
        }


        if (xmpDone == false) {
            newResLength += writeXmpData(xmpData_, outIo);
        }


        io_->populateFakeData();


        size_t readSize = 0;
        while ((readSize = io_->read(lbuf.pData_, lbuf.size_))) {
            if (outIo.write(lbuf.pData_, readSize) != readSize)
                throw Error(kerImageWriteFailed);
        }
        if (outIo.error())
            throw Error(kerImageWriteFailed);


#ifdef DEBUG
        std::cerr << "newResLength: " << newResLength << "\n";
#endif
        outIo.seek(resLenOffset, BasicIo::beg);
        ul2Data(buf, newResLength, bigEndian);
        if (outIo.write(buf, 4) != 4)
            throw Error(kerImageWriteFailed);

    }
