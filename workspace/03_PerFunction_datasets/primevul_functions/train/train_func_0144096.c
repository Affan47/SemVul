void JpegBase::writeMetadata()
    {
        if (io_->open() != 0) {
            throw Error(9, io_->path(), strError());
        }
        IoCloser closer(*io_);
        BasicIo::AutoPtr tempIo(io_->temporary());
        assert (tempIo.get() != 0);

        doWriteMetadata(*tempIo);
        io_->close();
        io_->transfer(*tempIo);
    }
