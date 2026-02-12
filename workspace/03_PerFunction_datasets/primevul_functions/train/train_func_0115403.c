void CrwImage::writeMetadata()
    {
#ifdef DEBUG
        std::cerr << "Writing CRW file " << io_->path() << "\n";
#endif

        DataBuf buf;
        if (io_->open() == 0) {
            IoCloser closer(*io_);

            if (isCrwType(*io_, false)) {

                buf.alloc((long) io_->size());
                io_->read(buf.pData_, buf.size_);
                if (io_->error() || io_->eof()) {
                    buf.reset();
                }
            }
        }

        Blob blob;
        CrwParser::encode(blob, buf.pData_, (uint32_t)buf.size_, this);


        MemIo::UniquePtr tempIo(new MemIo);
        assert(tempIo.get() != 0);
        tempIo->write((blob.size() > 0 ? &blob[0] : 0), static_cast<long>(blob.size()));
        io_->close();
        io_->transfer(*tempIo);

    }
