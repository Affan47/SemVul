WavInFile::WavInFile(FILE *file)
{

    fptr = file;
    if (!file)
    {

        string msg = "Error : Unable to access input stream for reading";
        ST_THROW_RT_ERROR(msg.c_str());
    }

    init();
}
