ScanLineInputFile::ScanLineInputFile
    (const Header &header,
     OPENEXR_IMF_INTERNAL_NAMESPACE::IStream *is,
     int numThreads)
:
    _data (new Data (numThreads)),
    _streamData (new InputStreamMutex())
{
    _streamData->is = is;
    _data->memoryMapped = is->isMemoryMapped();

    try
    {

        initialize(header);


        _data->version=0;
        readLineOffsets (*_streamData->is,
                        _data->lineOrder,
                        _data->lineOffsets,
                        _data->fileIsComplete);
    }
    catch(...)
    {
        if(_data)
        {
           if (!_data->memoryMapped)
           {
              for (size_t i = 0; i < _data->lineBuffers.size(); i++)
              {
                 if( _data->lineBuffers[i] )
                 {
                   EXRFreeAligned(_data->lineBuffers[i]->buffer);
                   _data->lineBuffers[i]->buffer=nullptr;
                 }
              }
           }
        }
        delete _streamData;
        delete _data;
        throw;
    }
}
