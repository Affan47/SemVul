bgav_mkv_targets_read(bgav_input_context_t * ctx,
                         bgav_mkv_targets_t * ret,
                         bgav_mkv_element_t * parent)
  {
  bgav_mkv_element_t e;
  while(ctx->position < parent->end)
    {
    if(!bgav_mkv_element_read(ctx, &e))
      return 0;

    switch(e.id)
      {
      case MKV_ID_TargetTypeValue:
        if(!mkv_read_uint_small(ctx, &ret->TargetTypeValue, e.size))
          return 0;
        break;
      case MKV_ID_TargetType:
        if(!mkv_read_string(ctx, &ret->TargetType, e.size))
          return 0;
        break;
      case MKV_ID_TagTrackUID:
        ret->TagTrackUID =
          realloc(ret->TagTrackUID,
                  (ret->num_TagTrackUID+1)*sizeof(*ret->TagTrackUID));
        if(!mkv_read_uint(ctx, ret->TagTrackUID + ret->num_TagTrackUID, e.size))
          return 0;
        ret->num_TagTrackUID++;
        break;
      case MKV_ID_TagEditionUID:
        ret->TagEditionUID =
          realloc(ret->TagEditionUID,
                  (ret->num_TagEditionUID+1)*sizeof(*ret->TagEditionUID));
        if(!mkv_read_uint(ctx, ret->TagEditionUID + ret->num_TagEditionUID, e.size))
          return 0;
        ret->num_TagEditionUID++;
        break;
      case MKV_ID_TagChapterUID:
        ret->TagChapterUID =
          realloc(ret->TagChapterUID,
                  (ret->num_TagChapterUID+1)*sizeof(*ret->TagChapterUID));
        if(!mkv_read_uint(ctx, ret->TagChapterUID + ret->num_TagChapterUID, e.size))
          return 0;
        ret->num_TagChapterUID++;
        break;
      case MKV_ID_TagAttachmentUID:
        ret->TagAttachmentUID =
          realloc(ret->TagAttachmentUID,
                  (ret->num_TagAttachmentUID+1)*sizeof(*ret->TagAttachmentUID));
        if(!mkv_read_uint(ctx, ret->TagAttachmentUID + ret->num_TagAttachmentUID, e.size))
          return 0;
        ret->num_TagAttachmentUID++;
        break;
      default:
        bgav_mkv_element_skip(ctx, &e, "target");
        break;
      }
    }
  return 1;
  }
