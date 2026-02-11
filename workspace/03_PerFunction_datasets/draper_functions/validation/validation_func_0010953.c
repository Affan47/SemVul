get_source_stream(bgav_track_table_t * tt,
                             mxf_file_t * f,
                             int * track_index, int * stream_index,
                             bgav_stream_type_t type,
                             mxf_package_t * sp, int track_id)
  {
  int i;
  mxf_content_storage_t * cs;
  int found;

  cs = (mxf_content_storage_t*)(((mxf_preface_t*)(f->header.preface))->content_storage);
  found = 0;
  *track_index = 0;

  for(i = 0; i < cs->num_package_refs; i++)
    {
    if(cs->packages[i]->type == MXF_TYPE_SOURCE_PACKAGE)
      {
      if(cs->packages[i] == (mxf_metadata_t*)sp)
        {
        found = 1;
        break;
        }
      else
        (*track_index)++;
      }
    }

  if(!found)
    return 0;

  switch(type)
    {
    case BGAV_STREAM_AUDIO:
      *stream_index = find_source_stream(tt->tracks[*track_index].audio_streams,
                                         tt->tracks[*track_index].num_audio_streams,
                                         track_id);
      break;
    case BGAV_STREAM_VIDEO:
      *stream_index = find_source_stream(tt->tracks[*track_index].video_streams,
                                         tt->tracks[*track_index].num_video_streams,
                                         track_id);
      break;
    case BGAV_STREAM_SUBTITLE_TEXT:
    case BGAV_STREAM_SUBTITLE_OVERLAY:
      *stream_index = find_source_stream(tt->tracks[*track_index].subtitle_streams,
                                         tt->tracks[*track_index].num_subtitle_streams,
                                         track_id);
      break;
    case BGAV_STREAM_UNKNOWN:
      break;
    }
  if(*stream_index < 0)
    return 0;
  return 1;
  }
