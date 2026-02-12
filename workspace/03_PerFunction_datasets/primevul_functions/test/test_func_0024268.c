ZipFile::OpenStreamCounter::~OpenStreamCounter()
{


    jassert (numOpenStreams == 0);
}
