inline void Http2Session::RemoveStream(Http2Stream* stream) {
  if (streams_.empty() || stream == nullptr)
    return;
  streams_.erase(stream->id());
  DecrementCurrentSessionMemory(sizeof(*stream));
}
