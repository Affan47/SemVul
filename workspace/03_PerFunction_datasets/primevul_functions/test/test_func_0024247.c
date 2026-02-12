void ZipFile::Builder::addEntry (InputStream* stream, int compression, const String& path, Time time)
{
    jassert (stream != nullptr);
    jassert (path.isNotEmpty());
    items.add (new Item ({}, stream, compression, path, time));
}
