write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);

    plNetMsgStreamHelper helper;
    unsigned char* buf = new unsigned char[fStream.size()];
    fStream.copyTo(buf, fStream.size());
    helper.setStream(buf, fStream.size());
    helper.setCompressionType(fCompressionType);

    helper.write(S, mgr);
    delete[] buf;
}
