long DataValue::copy(byte* buf, ByteOrder ) const
    {

        return static_cast<long>(
            std::copy(value_.begin(), value_.end(), buf) - buf
            );
    }
