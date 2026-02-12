int LibRaw::unpack(void)
{
  CHECK_ORDER_HIGH(LIBRAW_PROGRESS_LOAD_RAW);
  CHECK_ORDER_LOW(LIBRAW_PROGRESS_IDENTIFY);
  try {

    if(!libraw_internal_data.internal_data.input)
      return LIBRAW_INPUT_CLOSED;

    RUN_CALLBACK(LIBRAW_PROGRESS_LOAD_RAW,0,2);
    if (O.shot_select >= P1.raw_count)
      return LIBRAW_REQUEST_FOR_NONEXISTENT_IMAGE;

    if(!load_raw)
      return LIBRAW_UNSPECIFIED_ERROR;


    if(imgdata.image)
      {
        free(imgdata.image);
        imgdata.image = 0;
      }
    if(imgdata.rawdata.raw_alloc)
      {
        free(imgdata.rawdata.raw_alloc);
        imgdata.rawdata.raw_alloc = 0;
      }
    if (libraw_internal_data.unpacker_data.meta_length)
      {
        libraw_internal_data.internal_data.meta_data =
          (char *) malloc (libraw_internal_data.unpacker_data.meta_length);
        merror (libraw_internal_data.internal_data.meta_data, "LibRaw::unpack()");
      }

    libraw_decoder_info_t decoder_info;
    get_decoder_info(&decoder_info);

    int save_iwidth = S.iwidth, save_iheight = S.iheight, save_shrink = IO.shrink;

    int rwidth = S.raw_width, rheight = S.raw_height;
    if( !IO.fuji_width)
      {

        if(rwidth < S.width + S.left_margin)
          rwidth = S.width + S.left_margin;
        if(rheight < S.height + S.top_margin)
          rheight = S.height + S.top_margin;
      }

    imgdata.rawdata.raw_image = 0;
    imgdata.rawdata.color4_image = 0;
    imgdata.rawdata.color3_image = 0;
#ifdef USE_RAWSPEED

    if(O.use_rawspeed
       && !(is_sraw() && O.sraw_ycc)
       && (decoder_info.decoder_flags & LIBRAW_DECODER_TRYRAWSPEED) && _rawspeed_camerameta)
      {
        INT64 spos = ID.input->tell();
        void *_rawspeed_buffer = 0;
        try
          {

            ID.input->seek(0,SEEK_SET);
            INT64 _rawspeed_buffer_sz = ID.input->size()+32;
            _rawspeed_buffer = malloc(_rawspeed_buffer_sz);
            if(!_rawspeed_buffer) throw LIBRAW_EXCEPTION_ALLOC;
            ID.input->read(_rawspeed_buffer,_rawspeed_buffer_sz,1);
            FileMap map((uchar8*)_rawspeed_buffer,_rawspeed_buffer_sz);
            RawParser t(&map);
            RawDecoder *d = 0;
            CameraMetaDataLR *meta = static_cast<CameraMetaDataLR*>(_rawspeed_camerameta);
            d = t.getDecoder();
            if(!d) throw "Unable to find decoder";
            try {
              d->checkSupport(meta);
            }
            catch (const RawDecoderException& e)
              {
                imgdata.process_warnings |= LIBRAW_WARN_RAWSPEED_UNSUPPORTED;
                throw e;
              }
            d->interpolateBadPixels = FALSE;
            d->applyStage1DngOpcodes = FALSE;
            _rawspeed_decoder = static_cast<void*>(d);
            d->decodeRaw();
            d->decodeMetaData(meta);
            RawImage r = d->mRaw;
            if( r->errors.size()>0)
              {
                delete d;
                _rawspeed_decoder = 0;
                throw;
              }
            if (r->isCFA) {
              imgdata.rawdata.raw_image = (ushort*) r->getDataUncropped(0,0);
            } else if(r->getCpp()==4) {
              imgdata.rawdata.color4_image = (ushort(*)[4]) r->getDataUncropped(0,0);
			  C.maximum = r->whitePoint;
            } else if(r->getCpp() == 3)
              {
                imgdata.rawdata.color3_image = (ushort(*)[3]) r->getDataUncropped(0,0);
              }
            else
              {
                delete d;
                _rawspeed_decoder = 0;
              }
            if(_rawspeed_decoder)
              {

                iPoint2D rsdim = r->getUncroppedDim();
                S.raw_pitch = r->pitch;
                S.raw_width = rsdim.x;
                S.raw_height = rsdim.y;

                fix_after_rawspeed(r->blackLevel);
              }
            free(_rawspeed_buffer);
            _rawspeed_buffer = 0;
            imgdata.process_warnings |= LIBRAW_WARN_RAWSPEED_PROCESSED;
          }
        catch (...)
          {

            imgdata.process_warnings |= LIBRAW_WARN_RAWSPEED_PROBLEM;
            if(_rawspeed_buffer)
              {
                free(_rawspeed_buffer);
                _rawspeed_buffer = 0;
              }
          }
        ID.input->seek(spos,SEEK_SET);
      }
#endif
    if(!imgdata.rawdata.raw_image && !imgdata.rawdata.color4_image && !imgdata.rawdata.color3_image)
      {

        if(decoder_info.decoder_flags &  LIBRAW_DECODER_OWNALLOC)
          {


          }
        else if(decoder_info.decoder_flags &  LIBRAW_DECODER_FLATFIELD)
          {
            imgdata.rawdata.raw_alloc = malloc(rwidth*(rheight+7)*sizeof(imgdata.rawdata.raw_image[0]));
            imgdata.rawdata.raw_image = (ushort*) imgdata.rawdata.raw_alloc;
            if(!S.raw_pitch)
                S.raw_pitch = S.raw_width*2;
          }
        else if (decoder_info.decoder_flags & LIBRAW_DECODER_LEGACY)
          {

            S.iwidth = S.width;
            S.iheight= S.height;
            IO.shrink = 0;
            S.raw_pitch = S.width*8;

            imgdata.rawdata.raw_alloc = 0;
            imgdata.image = (ushort (*)[4]) calloc(S.iwidth*S.iheight,sizeof(*imgdata.image));
          }
        ID.input->seek(libraw_internal_data.unpacker_data.data_offset, SEEK_SET);

        unsigned m_save = C.maximum;
        if(load_raw == &LibRaw::unpacked_load_raw && !strcasecmp(imgdata.idata.make,"Nikon"))
          C.maximum=65535;
        (this->*load_raw)();
        if(load_raw == &LibRaw::unpacked_load_raw && !strcasecmp(imgdata.idata.make,"Nikon"))
          C.maximum = m_save;
        if(decoder_info.decoder_flags &  LIBRAW_DECODER_OWNALLOC)
          {


          }
        else if (decoder_info.decoder_flags & LIBRAW_DECODER_LEGACY)
          {

            imgdata.rawdata.raw_alloc = imgdata.image;
            imgdata.image = 0;


            S.raw_width = S.width;
            S.left_margin = 0;
            S.raw_height = S.height;
            S.top_margin = 0;
          }
      }

    if(imgdata.rawdata.raw_image)
      crop_masked_pixels();


    if( (decoder_info.decoder_flags & LIBRAW_DECODER_LEGACY) && !imgdata.rawdata.color4_image)
      {
        imgdata.image = 0;
        imgdata.rawdata.color4_image = (ushort (*)[4]) imgdata.rawdata.raw_alloc;
      }


    S.iwidth = save_iwidth;
    S.iheight = save_iheight;
    IO.shrink = save_shrink;


    unsigned int i = C.cblack[3];
    unsigned int c;
    for(c=0;c<3;c++)
      if (i > C.cblack[c]) i = C.cblack[c];
    for (c=0;c<4;c++)
      C.cblack[c] -= i;
    C.black += i;


    memmove(&imgdata.rawdata.color,&imgdata.color,sizeof(imgdata.color));
    memmove(&imgdata.rawdata.sizes,&imgdata.sizes,sizeof(imgdata.sizes));
    memmove(&imgdata.rawdata.iparams,&imgdata.idata,sizeof(imgdata.idata));
    memmove(&imgdata.rawdata.ioparams,&libraw_internal_data.internal_output_params,sizeof(libraw_internal_data.internal_output_params));

    SET_PROC_FLAG(LIBRAW_PROGRESS_LOAD_RAW);
    RUN_CALLBACK(LIBRAW_PROGRESS_LOAD_RAW,1,2);

    return 0;
  }
  catch ( LibRaw_exceptions err) {
    EXCEPTION_HANDLER(err);
  }
  catch (std::exception ee) {
    EXCEPTION_HANDLER(LIBRAW_EXCEPTION_IO_CORRUPT);
  }
}
