void MessageCompressorManager::clientFinish(const BSONObj& input) {
    auto elem = input.getField("compression");
    LOG(3) << "Finishing client-side compression negotiation";


    invariant(_negotiated.empty());


    if (elem.eoo()) {
        LOG(3) << "No compression algorithms were sent from the server. "
               << "This connection will be uncompressed";
        return;
    }

    LOG(3) << "Received message compressors from server";
    for (const auto& e : elem.Obj()) {
        auto algoName = e.checkAndGetStringData();
        auto ret = _registry->getCompressor(algoName);
        LOG(3) << "Adding compressor " << ret->getName();
        _negotiated.push_back(ret);
    }
}
