newLineBufferTask
    (TaskGroup *group,
     DeepScanLineInputFile::Data *ifd,
     int number,
     int scanLineMin,
     int scanLineMax)
{


    LineBuffer *lineBuffer = ifd->getLineBuffer (number);

    try
    {
        lineBuffer->wait ();

        if (lineBuffer->number != number)
        {
            lineBuffer->minY = ifd->minY + number * ifd->linesInBuffer;
            lineBuffer->maxY = lineBuffer->minY + ifd->linesInBuffer - 1;

            lineBuffer->number = number;
            lineBuffer->uncompressedData = 0;

            readPixelData (ifd->_streamData, ifd, lineBuffer->minY,
                           lineBuffer->buffer,
                           lineBuffer->packedDataSize,
                           lineBuffer->unpackedDataSize);
        }
    }
    catch (std::exception &e)
    {
        if (!lineBuffer->hasException)
        {
            lineBuffer->exception = e.what();
            lineBuffer->hasException = true;
        }
        lineBuffer->number = -1;
        lineBuffer->post();
        throw;
    }
    catch (...)
    {


        lineBuffer->exception = "unrecognized exception";
        lineBuffer->hasException = true;
        lineBuffer->number = -1;
        lineBuffer->post();
        throw;
    }

    scanLineMin = max (lineBuffer->minY, scanLineMin);
    scanLineMax = min (lineBuffer->maxY, scanLineMax);

    return new LineBufferTask (group, ifd, lineBuffer,
                               scanLineMin, scanLineMax);
}
