AddStream(MediaType type,
                                    const std::string& name,
                                    const std::string& sync_label) {
  streams.push_back(Stream(type, name, sync_label));

  if (type == MEDIA_TYPE_VIDEO)
    has_video = true;
  else if (type == MEDIA_TYPE_AUDIO)
    has_audio = true;
  else if (type == MEDIA_TYPE_DATA)
    has_data = true;
}
