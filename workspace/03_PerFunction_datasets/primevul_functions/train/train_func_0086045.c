HTTP2Codec::mapPriorityToDependency(uint8_t priority) const {


  return virtualPriorityNodes_.empty()
    ? 0
    : virtualPriorityNodes_[
        std::min(priority, uint8_t(virtualPriorityNodes_.size() - 1))];
}
