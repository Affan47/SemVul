WavInFile::WavInFile(const char *fileName)
{

    fptr = fopen(fileName, "rb");
    if (fptr == NULL)
    {

        string msg = "Error : Unable to open file \"";
        msg += fileName;
        msg += "\" for reading.";
        ST_THROW_RT_ERROR(msg.c_str());
    }

    init();
}
