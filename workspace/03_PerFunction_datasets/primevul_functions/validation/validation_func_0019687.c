ScanLineInputFile::setFrameBuffer (const FrameBuffer &frameBuffer)
{
#if ILMBASE_THREADING_ENABLED
    std::lock_guard<std::mutex> lock (*_streamData);
#endif

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


    bool optimizationPossible = true;

    if (!GLOBAL_SYSTEM_LITTLE_ENDIAN)
    {
        optimizationPossible =false;
    }

    vector<sliceOptimizationData> optData;


    vector<InSliceInfo> slices;
    ChannelList::ConstIterator i = channels.begin();


    size_t offset = 0;

    for (FrameBuffer::ConstIterator j = frameBuffer.begin();
	 j != frameBuffer.end();
	 ++j)
    {
	while (i != channels.end() && strcmp (i.name(), j.name()) < 0)
	{


	    slices.push_back (InSliceInfo (i.channel().type,
					   i.channel().type,
					   0,
					   0,
					   0,
					   i.channel().xSampling,
					   i.channel().ySampling,
					   false,
					   true,
					   0.0));

              switch(i.channel().type)
              {
                  case OPENEXR_IMF_INTERNAL_NAMESPACE::HALF :
                      offset++;
                      break;
                  case OPENEXR_IMF_INTERNAL_NAMESPACE::FLOAT :
                      offset+=2;
                      break;
                  case OPENEXR_IMF_INTERNAL_NAMESPACE::UINT :
                      offset+=2;
                      break;
                  case OPENEXR_IMF_INTERNAL_NAMESPACE::NUM_PIXELTYPES:
                  default:

                      break;
              }


              if (i.channel().xSampling!=1 || i.channel().ySampling!=1)
              {
                  optimizationPossible = false;
              }
              ++i;
	}

	bool fill = false;

	if (i == channels.end() || strcmp (i.name(), j.name()) > 0)
	{


	    fill = true;
	}

	slices.push_back (InSliceInfo (j.slice().type,
				       fill? j.slice().type:
				             i.channel().type,
				       j.slice().base,
				       j.slice().xStride,
				       j.slice().yStride,
				       j.slice().xSampling,
				       j.slice().ySampling,
				       fill,
				       false,
				       j.slice().fillValue));

          if(!fill && i.channel().type!=OPENEXR_IMF_INTERNAL_NAMESPACE::HALF)
          {
              optimizationPossible = false;
          }

          if(j.slice().type != OPENEXR_IMF_INTERNAL_NAMESPACE::HALF)
          {
              optimizationPossible = false;
          }
          if(j.slice().xSampling!=1 || j.slice().ySampling!=1)
          {
              optimizationPossible = false;
          }


          if(optimizationPossible)
          {
              sliceOptimizationData dat;
              dat.base = j.slice().base;
              dat.fill = fill;
              dat.fillValue = j.slice().fillValue;
              dat.offset = offset;
              dat.xStride = j.slice().xStride;
              dat.yStride = j.slice().yStride;
              dat.xSampling = j.slice().xSampling;
              dat.ySampling = j.slice().ySampling;
              optData.push_back(dat);
          }

          if(!fill)
          {
              switch(i.channel().type)
              {
                  case OPENEXR_IMF_INTERNAL_NAMESPACE::HALF :
                      offset++;
                      break;
                  case OPENEXR_IMF_INTERNAL_NAMESPACE::FLOAT :
                      offset+=2;
                      break;
                  case OPENEXR_IMF_INTERNAL_NAMESPACE::UINT :
                      offset+=2;
                      break;
                  case OPENEXR_IMF_INTERNAL_NAMESPACE::NUM_PIXELTYPES:
                  default:

                      break;
              }
          }


	if (i != channels.end() && !fill)
	    ++i;
    }


   if(optimizationPossible)
   {


       sort(optData.begin(),optData.end());
       _data->optimizationMode = detectOptimizationMode(optData);
   }

   if(!optimizationPossible || _data->optimizationMode._optimizable==false)
   {
       optData = vector<sliceOptimizationData>();
       _data->optimizationMode._optimizable=false;
   }


    _data->frameBuffer = frameBuffer;
    _data->slices = slices;
    _data->optimizationData = optData;
}
