void MessageCompressorManager::serverNegotiate(const BSONObj& input, BSONObjBuilder* output) {
    LOG(3) << "Starting server-side compression negotiation";

    auto elem = input.getField("compression");


    if (elem.eoo()) {


        if (_negotiated.size() > 0) {
            BSONArrayBuilder sub(output->subarrayStart("compression"));
            for (const auto& algo : _negotiated) {
                sub.append(algo->getName());
            }
            sub.doneFast();
        } else {
            LOG(3) << "Compression negotiation not requested by client";
        }
        return;
    }


    _negotiated.clear();


    BSONObj theirObj = elem.Obj();

    if (!theirObj.nFields()) {
        LOG(3) << "No compressors provided";
        return;
    }

    for (const auto& elem : theirObj) {
        MessageCompressorBase* cur;
        auto curName = elem.checkAndGetStringData();


        if ((cur = _registry->getCompressor(curName))) {
            LOG(3) << cur->getName() << " is supported";
            _negotiated.push_back(cur);
        } else {
            LOG(3) << curName << " is not supported";
        }
    }


    if (_negotiated.size() > 0) {
        BSONArrayBuilder sub(output->subarrayStart("compression"));
        for (auto algo : _negotiated) {
            sub.append(algo->getName());
        }
        sub.doneFast();
    } else {
        LOG(3) << "Could not agree on compressor to use";
    }
}
