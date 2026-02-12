TiledInputFile::setFrameBuffer (const FrameBuffer &frameBuffer)
{
    Lock lock (*_data->_streamData);


    const ChannelList &channels = _data->header.channels();

    for (FrameBuffer::ConstIterator j = frameBuffer.begin();
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


    vector<TInSliceInfo> slices;
    ChannelList::ConstIterator i = channels.begin();

    for (FrameBuffer::ConstIterator j = frameBuffer.begin();
         j != frameBuffer.end();
         ++j)
    {
        while (i != channels.end() && strcmp (i.name(), j.name()) < 0)
        {


            slices.push_back (TInSliceInfo (i.channel().type,
					    i.channel().type,
					    0,
					    0,
					    0,
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

        slices.push_back (TInSliceInfo (j.slice().type,
                                        fill? j.slice().type: i.channel().type,
                                        j.slice().base,
                                        j.slice().xStride,
                                        j.slice().yStride,
                                        fill,
                                        false,
                                        j.slice().fillValue,
                                        (j.slice().xTileCoords)? 1: 0,
                                        (j.slice().yTileCoords)? 1: 0));

        if (i != channels.end() && !fill)
            ++i;
    }

    while (i != channels.end())
    {


	slices.push_back (TInSliceInfo (i.channel().type,
					i.channel().type,
					0,
					0,
					0,
					false,
					true,
					0.0));
	++i;
    }


    _data->frameBuffer = frameBuffer;
    _data->slices = slices;
}
