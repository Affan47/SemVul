int JpegBase::advanceToMarker() const
    {
        int c = -1;

        while ((c=io_->getb()) != 0xff) {
            if (c == EOF)
                return -1;
        }


        while ((c=io_->getb()) == 0xff) {
            if (c == EOF)
                return -2;
        }
        return c;
    }
