processData(uchar* data, int length)
    {
        if (done)
            return Done;


        if (libPngError)
            return Error;

        curLoader = this;
        if (setjmp(png_jmpbuf(pngReadStruct)))
        {
            curLoader->libPngError = true;
            return Error;
        }


        png_process_data(pngReadStruct, pngInfoStruct, data, length);

        return length;
    }
