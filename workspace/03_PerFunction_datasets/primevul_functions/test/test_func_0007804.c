void RtmpProtocol::handle_C1_simple(const char *data){

    char handshake_head = HANDSHAKE_PLAINTEXT;
    onSendRawData(obtainBuffer(&handshake_head, 1));

    RtmpHandshake s1(0);
    onSendRawData(obtainBuffer((char *) &s1, C1_HANDSHARK_SIZE));

    onSendRawData(obtainBuffer(data + 1, C1_HANDSHARK_SIZE));

    _next_step_func = [this](const char *data, size_t len) {

        return handle_C2(data, len);
    };
}
