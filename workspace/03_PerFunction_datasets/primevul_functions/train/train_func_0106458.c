void checkOverflow(std::unique_ptr<MessageCompressorBase> compressor) {


    const std::string data =
        "We embrace reality. We apply high-quality thinking and rigor."
        "We have courage in our convictions but work hard to ensure biases "
        "or personal beliefs do not get in the way of finding the best solution.";
    ConstDataRange input(data.data(), data.size());


    std::array<char, 16> smallBuffer;
    DataRange smallOutput(smallBuffer.data(), smallBuffer.size());


    std::vector<char> normalBuffer;
    normalBuffer.resize(compressor->getMaxCompressedSize(data.size()));
    auto sws = compressor->compressData(input, DataRange(normalBuffer.data(), normalBuffer.size()));
    ASSERT_OK(sws);
    DataRange normalRange = DataRange(normalBuffer.data(), sws.getValue());


    ASSERT_NOT_OK(compressor->compressData(input, smallOutput));


    ASSERT_NOT_OK(compressor->decompressData(normalRange, smallOutput));


    std::vector<char> scratch;
    scratch.resize(data.size());
    ConstDataRange tooSmallRange(normalBuffer.data(), normalBuffer.size() / 2);
    ASSERT_NOT_OK(
        compressor->decompressData(tooSmallRange, DataRange(scratch.data(), scratch.size())));
}
