void PngImg::InitStorage_() {
    rowPtrs_.resize(info_.height, nullptr);

    size_t h = info_.height;
    size_t rb = info_.rowbytes;


    if (h > std::numeric_limits<size_t>::max() / rb) {

        throw std::runtime_error("Image is too large to allocate single buffer");
    }
    data_ = new png_byte[h * rb];

    for(size_t i = 0; i < info_.height; ++i) {
        rowPtrs_[i] = data_ + i * rb;
    }
}
