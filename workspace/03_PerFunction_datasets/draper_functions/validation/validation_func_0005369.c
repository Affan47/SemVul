checksum() const
{
    GooString *cs = d->emb_file->checksum();
    const char *ccs = cs->getCString();
    byte_array data(cs->getLength());
    for (int i = 0; i < cs->getLength(); ++i) {
        data[i] = ccs[i];
    }
    return data;
}
