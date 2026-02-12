int WavInFile::eof() const
{

    return (dataRead == header.data.data_len || feof(fptr));
}
