bgav_video_stream_keyframe_after(bgav_stream_t * s, int64_t time)
  {
  int pos;
  if(s->demuxer->index_mode == INDEX_MODE_SI_SA)
    {
    pos = s->first_index_position;
    while(pos <= s->last_index_position)
      {
      if((s->demuxer->si->entries[pos].stream_id == s->stream_id) &&
         (s->demuxer->si->entries[pos].flags & PACKET_FLAG_KEY) &&
         (s->demuxer->si->entries[pos].pts > time))
        {
        break;
        }
      pos++;
      }
    if(pos > s->last_index_position)
      return BGAV_TIMESTAMP_UNDEFINED;
    else
      return s->demuxer->si->entries[pos].pts;
    }
  else if(s->file_index)
    {
    if(time >= s->duration)
      {
      return BGAV_TIMESTAMP_UNDEFINED;
      }
    pos = file_index_seek(s->file_index, time);

    while((pos < s->file_index->num_entries - 1) &&
          ((s->file_index->entries[pos].pts <= time) ||
           !(s->file_index->entries[pos].flags & PACKET_FLAG_KEY)))
      pos++;

    if((s->file_index->entries[pos].pts <= time) ||
       !(s->file_index->entries[pos].flags & PACKET_FLAG_KEY))
      {
      return BGAV_TIMESTAMP_UNDEFINED;
      }
    return s->file_index->entries[pos].pts;
    }
  return BGAV_TIMESTAMP_UNDEFINED;

  }
