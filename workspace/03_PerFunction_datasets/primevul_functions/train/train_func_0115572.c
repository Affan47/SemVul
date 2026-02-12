byte PgfImage::readPgfMagicNumber(BasicIo& iIo)
    {
        byte b = iIo.getb();
        if (iIo.error()) throw Error(kerFailedToReadImageData);

        if (b < 0x36)
        {

#ifdef DEBUG
            std::cout << "Exiv2::PgfImage::readMetadata: wrong Magick number\n";
#endif
        }

        return b;
    }
