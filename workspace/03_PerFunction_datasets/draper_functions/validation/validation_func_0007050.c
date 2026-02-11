bgav_mkv_chapter_track_read(bgav_input_context_t * ctx,
                                  bgav_mkv_chapter_track_t * ret,
                                  bgav_mkv_element_t * parent)
  {
  bgav_mkv_element_t e;
  while(ctx->position < parent->end)
    {
    if(!bgav_mkv_element_read(ctx, &e))
      return 0;

    switch(e.id)
      {
      case MKV_ID_ChapterTrackNumber:
        if(!mkv_read_uint(ctx, &ret->ChapterTrackNumber, e.size))
          return 0;
        break;
      default:
        bgav_mkv_element_skip(ctx, &e, "chapter_track");
        break;
      }
    }
  return 1;
  }
