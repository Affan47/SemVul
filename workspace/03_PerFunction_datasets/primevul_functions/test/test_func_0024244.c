bool writeDirectoryEntry (OutputStream& target)
    {
        target.writeInt (0x02014b50);
        target.writeShort (symbolicLink ? 0x0314 : 0x0014);
        writeFlagsAndSizes (target);
        target.writeShort (0);
        target.writeShort (0);
        target.writeShort (0);
        target.writeInt ((int) (symbolicLink ? 0xA1ED0000 : 0));
        target.writeInt ((int) (uint32) headerStart);
        target << storedPathname;

        return true;
    }
