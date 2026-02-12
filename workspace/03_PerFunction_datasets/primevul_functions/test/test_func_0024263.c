TemporaryFile::~TemporaryFile()
{
    if (! deleteTemporaryFile())
    {


        jassertfalse;
    }
}
