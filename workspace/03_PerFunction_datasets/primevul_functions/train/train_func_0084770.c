DeepScanLineInputFile::setFrameBuffer (const DeepFrameBuffer &frameBuffer)
{
#if ILMTHREAD_THREADING_ENABLED
    std::lock_guard<std::mutex> lock (*_data->_streamData);
#endif


    const ChannelList &channels = _data->header.channels();

    for (DeepFrameBuffer::ConstIterator j = frameBuffer.begin();
         j != frameBuffer.end();
         ++j)
    {
        ChannelList::ConstIterator i = channels.find (j.name());

        if (i == channels.end())
            continue;

        if (i.channel().xSampling != j.slice().xSampling ||
            i.channel().ySampling != j.slice().ySampling)
            THROW (IEX_NAMESPACE::ArgExc, "X and/or y subsampling factors "
                                "of \"" << i.name() << "\" channel "
                                "of input file \"" << fileName() << "\" are "
                                "not compatible with the frame buffer's "
                                "subsampling factors.");
    }


    const Slice& sampleCountSlice = frameBuffer.getSampleCountSlice();
    if (sampleCountSlice.base == 0)
    {
        throw IEX_NAMESPACE::ArgExc ("Invalid base pointer, please set a proper sample count slice.");
    }
    else
    {
        _data->sampleCountSliceBase = sampleCountSlice.base;
        _data->sampleCountXStride = static_cast<int>(sampleCountSlice.xStride);
        _data->sampleCountYStride = static_cast<int>(sampleCountSlice.yStride);
    }


    vector<InSliceInfo*> slices;
    ChannelList::ConstIterator i = channels.begin();

    for (DeepFrameBuffer::ConstIterator j = frameBuffer.begin();
         j != frameBuffer.end();
         ++j)
    {
        while (i != channels.end() && strcmp (i.name(), j.name()) < 0)
        {


            slices.push_back (new InSliceInfo (i.channel().type,
                                               NULL,
                                               i.channel().type,
                                               0,
                                               0,
                                               0,
                                               i.channel().xSampling,
                                               i.channel().ySampling,
                                               false,
                                               true,
                                               0.0));
            ++i;
        }

        bool fill = false;

        if (i == channels.end() || strcmp (i.name(), j.name()) > 0)
        {


            fill = true;
        }

        slices.push_back (new InSliceInfo (j.slice().type,
                                           j.slice().base,
                                           fill? j.slice().type:
                                                 i.channel().type,
                                           j.slice().xStride,
                                           j.slice().yStride,
                                           j.slice().sampleStride,
                                           j.slice().xSampling,
                                           j.slice().ySampling,
                                           fill,
                                           false,
                                           j.slice().fillValue));


        if (i != channels.end() && !fill)
            ++i;
    }


    for (long i = 0; i < _data->gotSampleCount.size(); i++)
        _data->gotSampleCount[i] = false;
    for (size_t i = 0; i < _data->bytesPerLine.size(); i++)
        _data->bytesPerLine[i] = 0;


    _data->frameBuffer = frameBuffer;

    for (size_t i = 0; i < _data->slices.size(); i++)
        delete _data->slices[i];
    _data->slices = slices;
    _data->frameBufferValid = true;
}
