static bool ok_inflater_distance_with_tree(ok_inflater *inflater,
                                           const ok_inflater_huffman_tree *tree) {
    if (inflater->state_count < 0) {
        inflater->state_count = ok_inflater_decode_length(inflater, inflater->huffman_code);
        if (inflater->state_count < 0) {

            return false;
        }
        inflater->huffman_code = -1;
    }
    if (inflater->state_distance < 0) {
        inflater->state_distance = ok_inflater_decode_distance(inflater, tree);
        if (inflater->state_distance < 0) {

            return false;
        }
    }


    int buffer_offset = (inflater->buffer_end_pos - inflater->state_distance) & BUFFER_SIZE_MASK;
    if (inflater->state_distance == 1) {

        int n = inflater->state_count;
        int n2 = ok_inflater_write_byte_n(inflater, inflater->buffer[buffer_offset], n);
        inflater->state_count -= n2;
        if (n2 != n) {

            return false;
        }
    } else if (buffer_offset + inflater->state_count < BUFFER_SIZE) {

        int bytes_copyable = inflater->state_distance;
        while (inflater->state_count > 0) {
            int n = min(inflater->state_count, bytes_copyable);
            int n2 = ok_inflater_write_bytes(inflater, inflater->buffer + buffer_offset, n);
            inflater->state_count -= n2;
            bytes_copyable += n2;
            if (n2 != n) {

                return false;
            }
        }
    } else {

        while (inflater->state_count > 0) {
            int n = min(inflater->state_count, inflater->state_distance);
            n = min(n, (BUFFER_SIZE - buffer_offset));
            int n2 = ok_inflater_write_bytes(inflater, inflater->buffer + buffer_offset, n);
            inflater->state_count -= n2;
            buffer_offset = (buffer_offset + n2) & BUFFER_SIZE_MASK;
            if (n2 != n) {

                return false;
            }
        }
    }
    return true;
}
