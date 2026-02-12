inline StreamResource::~StreamResource() {
  while (listener_ != nullptr) {
    StreamListener* listener = listener_;
    listener->OnStreamDestroy();


    if (listener == listener_)
      RemoveStreamListener(listener_);
  }
}
