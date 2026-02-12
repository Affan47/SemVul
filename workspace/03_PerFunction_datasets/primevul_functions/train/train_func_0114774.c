void TiffImageEntry::doAccept(TiffVisitor& visitor)
    {
        visitor.visitImageEntry(this);
    }
