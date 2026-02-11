Mute(bool mute) {
  muted_ = mute;
  std::vector<Session*>::iterator it;
  for (it = sessions_.begin(); it != sessions_.end(); it++) {
    VoiceChannel* voice_channel = voice_channel_map_[(*it)->id()];
    if (voice_channel != NULL)
      voice_channel->Mute(mute);
  }
}
