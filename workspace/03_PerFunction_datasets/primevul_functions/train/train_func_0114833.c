void TiffEntry::doAccept(TiffVisitor& visitor)
    {
        visitor.visitEntry(this);
    }
