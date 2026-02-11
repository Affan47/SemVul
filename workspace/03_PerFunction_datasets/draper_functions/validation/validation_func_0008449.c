SendTo(const void* data, size_t size, const SocketAddress& addr) {
    ASSERT(!connected_ || addr == remote_addr_);
    if (server_addr_.IsAny() || type_ == SOCK_STREAM) {
      return socket_->SendTo(data, size, addr);
    }

    scoped_array<char> buf(new char[size + kNATEncodedIPv6AddressSize]);
    size_t addrlength = PackAddressForNAT(buf.get(),
                                          size + kNATEncodedIPv6AddressSize,
                                          addr);
    size_t encoded_size = size + addrlength;
    std::memcpy(buf.get() + addrlength, data, size);
    int result = socket_->SendTo(buf.get(), encoded_size, server_addr_);
    if (result >= 0) {
      ASSERT(result == static_cast<int>(encoded_size));
      result = result - static_cast<int>(addrlength);
    }
    return result;
  }
