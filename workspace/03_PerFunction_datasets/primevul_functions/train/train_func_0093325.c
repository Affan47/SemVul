ThreadHandoff crystallize_thread_handoff(abitreader *reader,
                                         const std::vector<std::pair<uint32_t, uint32_t> >&huff_input_offsets,
                                         int mcu_y,
                                         int lastdc[4],
                                         int luma_mul) {
    auto iter = std::lower_bound(huff_input_offsets.begin(), huff_input_offsets.end(),
                                 std::pair<uint32_t, uint32_t>(reader->getpos(), reader->getpos()));
    uint32_t mapped_item = 0;
    if (iter != huff_input_offsets.begin()) {
        --iter;
    }
    if (iter != huff_input_offsets.end()) {
        mapped_item = iter->second;
        mapped_item += reader->getpos() - iter->first;
    }

    ThreadHandoff retval = ThreadHandoff::zero();
    retval.segment_size = mapped_item;

    for (unsigned int i = 0; i < 4 && i < sizeof(retval.last_dc)/ sizeof(retval.last_dc[0]); ++i) {
        retval.last_dc[i] = lastdc[i];
        retval.luma_y_start = luma_mul * mcu_y;
        retval.luma_y_end = luma_mul * (mcu_y + 1);
    }

    std::tie( retval.num_overhang_bits, retval.overhang_byte ) = reader->overhang();


    return retval;
}
