int LibRaw::unpack(void)
{
  CHECK_ORDER_HIGH(LIBRAW_PROGRESS_LOAD_RAW);
  CHECK_ORDER_LOW(LIBRAW_PROGRESS_IDENTIFY);
  try
  {

    if (!libraw_internal_data.internal_data.input)
      return LIBRAW_INPUT_CLOSED;

    RUN_CALLBACK(LIBRAW_PROGRESS_LOAD_RAW, 0, 2);
    if (O.shot_select >= P1.raw_count)
      return LIBRAW_REQUEST_FOR_NONEXISTENT_IMAGE;

    if (!load_raw)
      return LIBRAW_UNSPECIFIED_ERROR;


    if (imgdata.image)
    {
      free(imgdata.image);
      imgdata.image = 0;
    }
    if (imgdata.rawdata.raw_alloc)
    {
      free(imgdata.rawdata.raw_alloc);
      imgdata.rawdata.raw_alloc = 0;
    }
    if (libraw_internal_data.unpacker_data.meta_length)
    {
      libraw_internal_data.internal_data.meta_data =
          (char *)malloc(libraw_internal_data.unpacker_data.meta_length);
      merror(libraw_internal_data.internal_data.meta_data, "LibRaw::unpack()");
    }

    libraw_decoder_info_t decoder_info;
    get_decoder_info(&decoder_info);

    int save_iwidth = S.iwidth, save_iheight = S.iheight,
        save_shrink = IO.shrink;

    int rwidth = S.raw_width, rheight = S.raw_height;
    if (!IO.fuji_width)
    {

      if (rwidth < S.width + S.left_margin)
        rwidth = S.width + S.left_margin;
      if (rheight < S.height + S.top_margin)
        rheight = S.height + S.top_margin;
    }
    if (rwidth > 65535 ||
        rheight > 65535)
      throw LIBRAW_EXCEPTION_IO_CORRUPT;

    imgdata.rawdata.raw_image = 0;
    imgdata.rawdata.color4_image = 0;
    imgdata.rawdata.color3_image = 0;
    imgdata.rawdata.float_image = 0;
    imgdata.rawdata.float3_image = 0;

#ifdef USE_DNGSDK
    if (imgdata.idata.dng_version && dnghost
        && libraw_internal_data.unpacker_data.tiff_samples != 2
        && valid_for_dngsdk() && load_raw != &LibRaw::pentax_4shot_load_raw)
    {

      INT64 pixcount =
          INT64(MAX(S.width, S.raw_width)) * INT64(MAX(S.height, S.raw_height));
      INT64 planecount =
          (imgdata.idata.filters || P1.colors == 1) ? 1 : LIM(P1.colors, 3, 4);
      INT64 samplesize = is_floating_point() ? 4 : 2;
      INT64 bytes = pixcount * planecount * samplesize;
      if (bytes > INT64(imgdata.params.max_raw_memory_mb) * INT64(1024 * 1024))
        throw LIBRAW_EXCEPTION_TOOBIG;


      int rr = try_dngsdk();
      if (raw_was_read())
        imgdata.process_warnings |= LIBRAW_WARN_DNGSDK_PROCESSED;
    }
#endif

#ifdef USE_RAWSPEED
    if (!raw_was_read())
    {
      int rawspeed_enabled = 1;

      if (imgdata.idata.dng_version && (libraw_internal_data.unpacker_data.tiff_samples == 2 || imgdata.idata.raw_count > 1))
        rawspeed_enabled = 0;

      if (libraw_internal_data.unpacker_data.is_NikonTransfer)
        rawspeed_enabled = 0;

      if (libraw_internal_data.unpacker_data.pana_encoding == 5)
        rawspeed_enabled = 0;

      if (imgdata.idata.raw_count > 1)
        rawspeed_enabled = 0;
      if (!strncasecmp(imgdata.idata.software, "Magic", 5))
        rawspeed_enabled = 0;

      if (!strncasecmp(imgdata.idata.make, "Olympus", 7) &&
          ((imgdata.sizes.raw_width > 6000) ||
           !strncasecmp(imgdata.idata.model, "SH-2", 4) ||
           !strncasecmp(imgdata.idata.model, "SH-3", 4) ||
           !strncasecmp(imgdata.idata.model, "TG-4", 4) ||
           !strncasecmp(imgdata.idata.model, "TG-5", 4) ||
           !strncasecmp(imgdata.idata.model, "TG-6", 4)))
        rawspeed_enabled = 0;

      if (!strncasecmp(imgdata.idata.make, "Canon", 5) &&
          !strcasecmp(imgdata.idata.model, "EOS 6D Mark II"))
        rawspeed_enabled = 0;

      if (imgdata.idata.dng_version && imgdata.idata.filters == 0 &&
          libraw_internal_data.unpacker_data.tiff_bps == 8)
        rawspeed_enabled = 0;

      if (load_raw == &LibRaw::packed_load_raw &&
          !strncasecmp(imgdata.idata.make, "Nikon", 5) &&
          (!strncasecmp(imgdata.idata.model, "E", 1) ||
           !strncasecmp(imgdata.idata.model, "COOLPIX B", 9) ||
           !strncasecmp(imgdata.idata.model, "COOLPIX P1000", 13)))
        rawspeed_enabled = 0;

      if (load_raw == &LibRaw::nikon_load_raw &&
          !strncasecmp(imgdata.idata.make, "Nikon", 5) &&
          !strncasecmp(imgdata.idata.model, "Z", 1))
        rawspeed_enabled = 0;

      if (load_raw == &LibRaw::panasonic_load_raw &&
          libraw_internal_data.unpacker_data.pana_encoding > 4)
        rawspeed_enabled = 0;


      if (O.use_rawspeed && rawspeed_enabled &&
          !(is_sraw() && (O.raw_processing_options &
                          (LIBRAW_PROCESSING_SRAW_NO_RGB |
                           LIBRAW_PROCESSING_SRAW_NO_INTERPOLATE))) &&
          (decoder_info.decoder_flags & LIBRAW_DECODER_TRYRAWSPEED) &&
          _rawspeed_camerameta)
      {
        INT64 pixcount = INT64(MAX(S.width, S.raw_width)) *
                         INT64(MAX(S.height, S.raw_height));
        INT64 planecount = (imgdata.idata.filters || P1.colors == 1)
                               ? 1
                               : LIM(P1.colors, 3, 4);
        INT64 bytes =
            pixcount * planecount * 2;
        if (bytes >
            INT64(imgdata.params.max_raw_memory_mb) * INT64(1024 * 1024))
          throw LIBRAW_EXCEPTION_TOOBIG;

        int rr = try_rawspeed();
      }
    }
#endif
    if (!raw_was_read())
    {

      int zero_rawimage = 0;
      if (decoder_info.decoder_flags & LIBRAW_DECODER_OWNALLOC)
      {


      }
      if (decoder_info.decoder_flags & LIBRAW_DECODER_SINAR4SHOT)
      {
        if (imgdata.params.shot_select)
        {
          if (INT64(rwidth) * INT64(rheight + 8) *
                  sizeof(imgdata.rawdata.raw_image[0]) >
              INT64(imgdata.params.max_raw_memory_mb) * INT64(1024 * 1024))
            throw LIBRAW_EXCEPTION_TOOBIG;
          imgdata.rawdata.raw_alloc = malloc(
              rwidth * (rheight + 8) * sizeof(imgdata.rawdata.raw_image[0]));
          imgdata.rawdata.raw_image = (ushort *)imgdata.rawdata.raw_alloc;
          if (!S.raw_pitch)
            S.raw_pitch = S.raw_width * 2;
        }
        else
        {
          if (INT64(rwidth) * INT64(rheight + 8) *
                  sizeof(imgdata.rawdata.raw_image[0]) * 4 >
              INT64(imgdata.params.max_raw_memory_mb) * INT64(1024 * 1024))
            throw LIBRAW_EXCEPTION_TOOBIG;
          S.raw_pitch = S.raw_width * 8;
          imgdata.rawdata.raw_alloc = 0;
          imgdata.image = (ushort(*)[4])calloc(
              unsigned(MAX(S.width, S.raw_width)) *
                  unsigned(MAX(S.height, S.raw_height) + 8),
              sizeof(*imgdata.image));
        }
      }
      else if (decoder_info.decoder_flags & LIBRAW_DECODER_3CHANNEL)
      {
        if (INT64(rwidth) * INT64(rheight + 8) *
                sizeof(imgdata.rawdata.raw_image[0]) * 3 >
            INT64(imgdata.params.max_raw_memory_mb) * INT64(1024 * 1024))
          throw LIBRAW_EXCEPTION_TOOBIG;

        imgdata.rawdata.raw_alloc = malloc(
            rwidth * (rheight + 8) * sizeof(imgdata.rawdata.raw_image[0]) * 3);
        imgdata.rawdata.color3_image = (ushort(*)[3])imgdata.rawdata.raw_alloc;
        if (!S.raw_pitch)
          S.raw_pitch = S.raw_width * 6;
      }
      else if (imgdata.idata.filters ||
               P1.colors ==
                   1)
      {
        if (INT64(rwidth) * INT64(rheight + 8) *
                sizeof(imgdata.rawdata.raw_image[0]) >
            INT64(imgdata.params.max_raw_memory_mb) * INT64(1024 * 1024))
          throw LIBRAW_EXCEPTION_TOOBIG;
        imgdata.rawdata.raw_alloc = malloc(
            rwidth * (rheight + 8) * sizeof(imgdata.rawdata.raw_image[0]));
        imgdata.rawdata.raw_image = (ushort *)imgdata.rawdata.raw_alloc;
        if (!S.raw_pitch)
          S.raw_pitch = S.raw_width * 2;
      }
      else

      {
        if (decoder_info.decoder_flags & LIBRAW_DECODER_ADOBECOPYPIXEL)
        {
          S.raw_pitch = S.raw_width * 8;
        }
        else
        {
          S.iwidth = S.width;
          S.iheight = S.height;
          IO.shrink = 0;
          if (!S.raw_pitch)
            S.raw_pitch = (decoder_info.decoder_flags &
                           LIBRAW_DECODER_LEGACY_WITH_MARGINS)
                              ? S.raw_width * 8
                              : S.width * 8;
        }


        if (INT64(MAX(S.width, S.raw_width)) *
                INT64(MAX(S.height, S.raw_height) + 8) *
                sizeof(*imgdata.image) >
            INT64(imgdata.params.max_raw_memory_mb) * INT64(1024 * 1024))
          throw LIBRAW_EXCEPTION_TOOBIG;

        imgdata.rawdata.raw_alloc = 0;
        imgdata.image =
            (ushort(*)[4])calloc(unsigned(MAX(S.width, S.raw_width)) *
                                     unsigned(MAX(S.height, S.raw_height) + 8),
                                 sizeof(*imgdata.image));
        if (!(decoder_info.decoder_flags & LIBRAW_DECODER_ADOBECOPYPIXEL))
        {
          imgdata.rawdata.raw_image = (ushort *)imgdata.image;
          zero_rawimage = 1;
        }
      }
      ID.input->seek(libraw_internal_data.unpacker_data.data_offset, SEEK_SET);

      unsigned m_save = C.maximum;
      if (load_raw == &LibRaw::unpacked_load_raw &&
          (!strcasecmp(imgdata.idata.make, "Nikon") || !strcasecmp(imgdata.idata.make, "Hasselblad"))
          )
        C.maximum = 65535;
      (this->*load_raw)();
      if (zero_rawimage)
        imgdata.rawdata.raw_image = 0;
      if (load_raw == &LibRaw::unpacked_load_raw &&
          (!strcasecmp(imgdata.idata.make, "Nikon") || !strcasecmp(imgdata.idata.make, "Hasselblad"))
          )
        C.maximum = m_save;
      if (decoder_info.decoder_flags & LIBRAW_DECODER_OWNALLOC)
      {

      }
      else if (decoder_info.decoder_flags & LIBRAW_DECODER_SINAR4SHOT &&
               imgdata.params.shot_select == 0)
      {
        imgdata.rawdata.raw_alloc = imgdata.image;
        imgdata.rawdata.color4_image = (ushort(*)[4])imgdata.rawdata.raw_alloc;
        imgdata.image = 0;
      }
      else if (!(imgdata.idata.filters ||
                 P1.colors == 1))
      {

        imgdata.rawdata.raw_alloc = imgdata.image;
        imgdata.rawdata.color4_image = (ushort(*)[4])imgdata.rawdata.raw_alloc;
        imgdata.image = 0;


        if (!(libraw_internal_data.unpacker_data.load_flags & 256) &&
            !(decoder_info.decoder_flags & LIBRAW_DECODER_ADOBECOPYPIXEL) &&
            !(decoder_info.decoder_flags & LIBRAW_DECODER_LEGACY_WITH_MARGINS))
        {
          S.raw_width = S.width;
          S.left_margin = 0;
          S.raw_height = S.height;
          S.top_margin = 0;
        }
      }
    }

    if (imgdata.rawdata.raw_image)
      crop_masked_pixels();


    S.iwidth = save_iwidth;
    S.iheight = save_iheight;
    IO.shrink = save_shrink;


    unsigned int i = C.cblack[3];
    unsigned int c;
    for (c = 0; c < 3; c++)
      if (i > C.cblack[c])
        i = C.cblack[c];
    for (c = 0; c < 4; c++)
      C.cblack[c] -= i;
    C.black += i;


    memmove(&imgdata.rawdata.color, &imgdata.color, sizeof(imgdata.color));
    memmove(&imgdata.rawdata.sizes, &imgdata.sizes, sizeof(imgdata.sizes));
    memmove(&imgdata.rawdata.iparams, &imgdata.idata, sizeof(imgdata.idata));
    memmove(&imgdata.rawdata.ioparams,
            &libraw_internal_data.internal_output_params,
            sizeof(libraw_internal_data.internal_output_params));

    SET_PROC_FLAG(LIBRAW_PROGRESS_LOAD_RAW);
    RUN_CALLBACK(LIBRAW_PROGRESS_LOAD_RAW, 1, 2);

    return 0;
  }
  catch (LibRaw_exceptions err)
  {
    EXCEPTION_HANDLER(err);
  }
  catch (std::exception ee)
  {
    EXCEPTION_HANDLER(LIBRAW_EXCEPTION_IO_CORRUPT);
  }
}
