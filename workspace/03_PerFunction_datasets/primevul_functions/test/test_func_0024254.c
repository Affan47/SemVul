void writeFlagsAndSizes (OutputStream& target) const
    {
        target.writeShort (10);
        target.writeShort ((short) (1 << 11));
        target.writeShort ((! symbolicLink && compressionLevel > 0) ? (short) 8 : (short) 0);
        writeTimeAndDate (target, fileTime);
        target.writeInt ((int) checksum);
        target.writeInt ((int) (uint32) compressedSize);
        target.writeInt ((int) (uint32) uncompressedSize);
        target.writeShort (static_cast<short> (storedPathname.toUTF8().sizeInBytes() - 1));
        target.writeShort (0);
    }
