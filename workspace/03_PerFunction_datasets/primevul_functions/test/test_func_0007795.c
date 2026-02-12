const char* RtmpProtocol::handle_rtmp(const char *data, size_t len) {
    auto ptr = data;
    while (len) {
        size_t offset = 0;
        auto header = (RtmpHeader *) ptr;
        auto header_len = HEADER_LENGTH[header->fmt];
        _now_chunk_id = header->chunk_id;
        switch (_now_chunk_id) {
            case 0: {


                if (len < 2) {

                    return ptr;
                }
                _now_chunk_id = 64 + (uint8_t) (ptr[1]);
                offset = 1;
                break;
            }

            case 1: {


                if (len < 3) {

                    return ptr;
                }
                _now_chunk_id = 64 + ((uint8_t) (ptr[2]) << 8) + (uint8_t) (ptr[1]);
                offset = 2;
                break;
            }


            default : break;
        }

        if (len < header_len + offset) {

            return ptr;
        }
        header = (RtmpHeader *) (ptr + offset);
        auto &pr = _map_chunk_data[_now_chunk_id];
        auto &now_packet = pr.first;
        auto &last_packet = pr.second;
        if (!now_packet) {
            now_packet = RtmpPacket::create();
            if (last_packet) {

                *now_packet = *last_packet;
            }

            now_packet->is_abs_stamp = false;
        }
        auto &chunk_data = *now_packet;
        chunk_data.chunk_id = _now_chunk_id;
        switch (header_len) {
            case 12:
                chunk_data.is_abs_stamp = true;
                chunk_data.stream_index = load_le32(header->stream_index);
            case 8:
                chunk_data.body_size = load_be24(header->body_size);
                chunk_data.type_id = header->type_id;
            case 4:
                chunk_data.ts_field = load_be24(header->time_stamp);
        }

        auto time_stamp = chunk_data.ts_field;
        if (chunk_data.ts_field == 0xFFFFFF) {
            if (len < header_len + offset + 4) {

                return ptr;
            }
            time_stamp = load_be32(ptr + offset + header_len);
            offset += 4;
        }

        if (chunk_data.body_size < chunk_data.buffer.size()) {
            throw std::runtime_error("非法的bodySize");
        }

        auto more = min(_chunk_size_in, (size_t) (chunk_data.body_size - chunk_data.buffer.size()));
        if (len < header_len + offset + more) {

            return ptr;
        }
        if (more) {
            chunk_data.buffer.append(ptr + header_len + offset, more);
        }
        ptr += header_len + offset + more;
        len -= header_len + offset + more;
        if (chunk_data.buffer.size() == chunk_data.body_size) {

            _now_stream_index = chunk_data.stream_index;
            chunk_data.time_stamp = time_stamp + (chunk_data.is_abs_stamp ? 0 : chunk_data.time_stamp);

            last_packet = now_packet;
            if (chunk_data.body_size) {
                handle_chunk(std::move(now_packet));
            } else {
                now_packet = nullptr;
            }
        }
    }
    return ptr;
}
