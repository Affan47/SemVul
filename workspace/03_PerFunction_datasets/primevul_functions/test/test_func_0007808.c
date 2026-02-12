void RtmpProtocol::sendRequest(int cmd, const string& str) {
    if (cmd <= MSG_SET_PEER_BW) {

        sendRtmp(cmd, _stream_index, str, 0, CHUNK_NETWORK);
    } else {

        sendRtmp(cmd, _stream_index, str, 0, CHUNK_SYSTEM);
    }
}
