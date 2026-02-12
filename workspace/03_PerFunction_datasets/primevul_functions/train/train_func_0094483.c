BufferedRandomDevice::BufferedRandomDevice(size_t bufferSize)
  : bufferSize_(bufferSize),
    buffer_(new unsigned char[bufferSize]),
    ptr_(buffer_.get() + bufferSize) {
  call_once(flag, [this]() {
    detail::AtFork::registerHandler(
        this,
         []() { return true; },
         []() {},

        []() {
          using Single = SingletonThreadLocal<BufferedRandomDevice, RandomTag>;
          auto& t = Single::get();


          t.ptr_ = t.buffer_.get() + t.bufferSize_;
        });
  });
}
