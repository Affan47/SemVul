build_file_index_mpeg(bgav_t * b)
  {
  int j;
  int64_t old_position;
  int callback_count = 0;
  old_position = b->input->position;

  while(1)
    {

    if(!bgav_demuxer_next_packet(b->demuxer))
      return 1;

    for(j = 0; j < b->tt->cur->num_audio_streams; j++)
      {
      if(!flush_stream_mpeg_audio(&b->tt->cur->audio_streams[j]))
        return 0;
      }
    for(j = 0; j < b->tt->cur->num_video_streams; j++)
      {
      if(!flush_stream_mpeg_video(&b->tt->cur->video_streams[j], 0))
        return 0;
      }
    for(j = 0; j < b->tt->cur->num_subtitle_streams; j++)
      {
      if(!b->tt->cur->subtitle_streams[j].data.subtitle.subreader)
        {
        if(!flush_stream_mpeg_subtitle(&b->tt->cur->subtitle_streams[j]))
          return 0;
        }
      }

    if(b->opt.index_callback && !(callback_count % 100))
      b->opt.index_callback(b->opt.index_callback_data,
                            (float)b->input->position /
                            (float)b->input->total_bytes);
    callback_count++;
    }

  for(j = 0; j < b->tt->cur->num_video_streams; j++)
    {
    if(!flush_stream_mpeg_video(&b->tt->cur->video_streams[j], 1))
      return 0;
    }


  bgav_input_seek(b->input, old_position, SEEK_SET);
  return 1;
  }
