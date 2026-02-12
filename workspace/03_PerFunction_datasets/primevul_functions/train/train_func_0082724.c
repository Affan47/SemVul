void PsdImage::readMetadata()
    {
#ifdef DEBUG
        std::cerr << "Exiv2::PsdImage::readMetadata: Reading Photoshop file " << io_->path() << "\n";
#endif
        if (io_->open() != 0)
        {
            throw Error(kerDataSourceOpenFailed, io_->path(), strError());
        }
        IoCloser closer(*io_);

        if (!isPsdType(*io_, false))
        {
            if (io_->error() || io_->eof()) throw Error(kerFailedToReadImageData);
            throw Error(kerNotAnImage, "Photoshop");
        }
        clearMetadata();


        byte buf[26];
        if (io_->read(buf, 26) != 26)
        {
            throw Error(kerNotAnImage, "Photoshop");
        }
        pixelWidth_ = getLong(buf + 18, bigEndian);
        pixelHeight_ = getLong(buf + 14, bigEndian);


        if (io_->read(buf, 4) != 4)
        {
            throw Error(kerNotAnImage, "Photoshop");
        }


        uint32_t colorDataLength = getULong(buf, bigEndian);
        if (io_->seek(colorDataLength, BasicIo::cur))
        {
            throw Error(kerNotAnImage, "Photoshop");
        }


        if (io_->read(buf, 4) != 4)
        {
            throw Error(kerNotAnImage, "Photoshop");
        }
        uint32_t resourcesLength = getULong(buf, bigEndian);
        while (resourcesLength > 0)
        {
            if (io_->read(buf, 8) != 8)
            {
                throw Error(kerNotAnImage, "Photoshop");
            }

            if (!Photoshop::isIrb(buf, 4))
            {
                break;
            }
            uint16_t resourceId = getUShort(buf + 4, bigEndian);
            uint32_t resourceNameLength = buf[6] & ~1;


            io_->seek(resourceNameLength, BasicIo::cur);


            if (io_->read(buf, 4) != 4)
            {
                throw Error(kerNotAnImage, "Photoshop");
            }
            uint32_t resourceSize = getULong(buf, bigEndian);
            uint32_t curOffset = io_->tell();

#ifdef DEBUG
        std::cerr << std::hex << "resourceId: " << resourceId << std::dec << " length: " << resourceSize << std::hex << "\n";
#endif

            readResourceBlock(resourceId, resourceSize);
            resourceSize = (resourceSize + 1) & ~1;
            io_->seek(curOffset + resourceSize, BasicIo::beg);
            resourcesLength -= (12 + resourceNameLength + resourceSize);
        }

    }
