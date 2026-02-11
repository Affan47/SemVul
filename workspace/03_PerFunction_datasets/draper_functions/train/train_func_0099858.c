OnPortDestroyed(Port* port) {
  ASSERT(worker_thread_ == talk_base::Thread::Current());


  std::vector<Port*>::iterator iter =
      std::find(ports_.begin(), ports_.end(), port);
  if (iter != ports_.end())
    ports_.erase(iter);

  LOG(INFO) << "Removed port from p2p socket: "
            << static_cast<int>(ports_.size()) << " remaining";
}
