setup_video_stream(bgav_demuxer_context_t * ctx,
                              fourxm_chunk_t * parent,
                              float framerate)
  {
  uint32_t width, height;
  fourxm_chunk_t chunk;
  bgav_stream_t * s;
  fourxm_priv_t * priv = ctx->priv;

  while(ctx->input->position < parent->end_pos)
    {
    if(!read_chunk_header(ctx->input, &chunk))
      return 0;

    switch(chunk.fourcc)
      {
      case ID_vtrk:
        s = bgav_track_add_video_stream(ctx->tt->cur, ctx->opt);

        bgav_input_skip(ctx->input, 8);

        if(bgav_input_read_data(ctx->input, priv->video_tag, 4) < 4)
          return 0;

        bgav_stream_set_extradata(s, priv->video_tag, 4);
        bgav_input_skip(ctx->input, 16);

        if(!bgav_input_read_32_le(ctx->input, &width) ||
           !bgav_input_read_32_le(ctx->input, &height))
          return 0;

        s->data.video.format.image_width = width;
        s->data.video.format.frame_width = width;

        s->data.video.format.image_height = height;
        s->data.video.format.frame_height = height;

        s->data.video.format.pixel_width  = 1;
        s->data.video.format.pixel_height = 1;

        s->data.video.format.timescale      = 1000000;
        s->data.video.format.frame_duration = 1000000.0/framerate;


        priv->video_pts = - s->data.video.format.frame_duration;
        s->fourcc = BGAV_MK_FOURCC('4','X','M','V');


#if 1
        bgav_input_skip(ctx->input, 4);
        bgav_input_skip(ctx->input, 4);
        bgav_input_skip(ctx->input, 75 - 52 + 1);
#endif
        break;
      default:
        skip_chunk(ctx->input, &chunk);
      }


    }
  return 1;
  }
