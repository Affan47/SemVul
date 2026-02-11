GetInitialPorts() {
  network_thread_ = talk_base::Thread::Current();
  if (!socket_factory_) {
    owned_socket_factory_.reset(
        new talk_base::BasicPacketSocketFactory(network_thread_));
    socket_factory_ = owned_socket_factory_.get();
  }

  network_thread_->Post(this, MSG_CONFIG_START);

  if (flags() & PORTALLOCATOR_ENABLE_SHAKER)
    network_thread_->PostDelayed(ShakeDelay(), this, MSG_SHAKE);
}
