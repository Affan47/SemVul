int WavInFile::read(short *buffer, int maxElems)
{
    unsigned int afterDataRead;
    int numBytes;
    int numElems;

    assert(buffer);
    switch (header.format.bits_per_sample)
    {
        case 8:
        {

            unsigned char *temp = (unsigned char*)getConvBuffer(maxElems);
            int i;

            numElems = read(temp, maxElems);

            for (i = 0; i < numElems; i ++)
            {
                buffer[i] = (short)(((short)temp[i] - 128) * 256);
            }
            break;
        }

        case 16:
        {


            assert(sizeof(short) == 2);

            numBytes = maxElems * 2;
            afterDataRead = dataRead + numBytes;
            if (afterDataRead > header.data.data_len)
            {

                numBytes = (int)header.data.data_len - (int)dataRead;
                assert(numBytes >= 0);
            }

            numBytes = (int)fread(buffer, 1, numBytes, fptr);
            dataRead += numBytes;
            numElems = numBytes / 2;


            _swap16Buffer((short *)buffer, numElems);
            break;
        }

        default:
        {
            stringstream ss;
            ss << "\nOnly 8/16 bit sample WAV files supported in integer compilation. Can't open WAV file with ";
            ss << (int)header.format.bits_per_sample;
            ss << " bit sample format. ";
            ST_THROW_RT_ERROR(ss.str().c_str());
        }
    };

    return numElems;
}
