DeepScanLineInputFile::readPixels (int scanLine1, int scanLine2)
{
    try
    {
#if ILMTHREAD_THREADING_ENABLED
        std::lock_guard<std::mutex> lock (*_data->_streamData);
#endif
        if (_data->slices.size() == 0)
            throw IEX_NAMESPACE::ArgExc ("No frame buffer specified "
                               "as pixel data destination.");

        int scanLineMin = min (scanLine1, scanLine2);
        int scanLineMax = max (scanLine1, scanLine2);

        if (scanLineMin < _data->minY || scanLineMax > _data->maxY)
            throw IEX_NAMESPACE::ArgExc ("Tried to read scan line outside "
                               "the image file's data window.");

        for (int i = scanLineMin; i <= scanLineMax; i++)
        {
            if (_data->gotSampleCount[i - _data->minY] == false)
                throw IEX_NAMESPACE::ArgExc ("Tried to read scan line without "
                                   "knowing the sample counts, please"
                                   "read the sample counts first.");
        }


        int start, stop, dl;

        if (_data->lineOrder == INCREASING_Y)
        {
            start = (scanLineMin - _data->minY) / _data->linesInBuffer;
            stop  = (scanLineMax - _data->minY) / _data->linesInBuffer + 1;
            dl = 1;
        }
        else
        {
            start = (scanLineMax - _data->minY) / _data->linesInBuffer;
            stop  = (scanLineMin - _data->minY) / _data->linesInBuffer - 1;
            dl = -1;
        }


        {
            TaskGroup taskGroup;


            for (int l = start; l != stop; l += dl)
            {
                ThreadPool::addGlobalTask (newLineBufferTask (&taskGroup,
                                                              _data, l,
                                                              scanLineMin,
                                                              scanLineMax));
            }


        }


        const string *exception = 0;

        for (size_t i = 0; i < _data->lineBuffers.size(); ++i)
        {
            LineBuffer *lineBuffer = _data->lineBuffers[i];

            if (lineBuffer->hasException && !exception)
                exception = &lineBuffer->exception;

            lineBuffer->hasException = false;
        }

        if (exception)
            throw IEX_NAMESPACE::IoExc (*exception);
    }
    catch (IEX_NAMESPACE::BaseExc &e)
    {
        REPLACE_EXC (e, "Error reading pixel data from image "
                     "file \"" << fileName() << "\". " << e.what());
        throw;
    }
}
