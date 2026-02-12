void RtmpProtocol::startClientSession(const function<void()> &func) {

    char handshake_head = HANDSHAKE_PLAINTEXT;
    onSendRawData(obtainBuffer(&handshake_head, 1));
    RtmpHandshake c1(0);
    c1.create_complex_c0c1();
    onSendRawData(obtainBuffer((char *) (&c1), sizeof(c1)));
    _next_step_func = [this, func](const char *data, size_t len) {

        return handle_S0S1S2(data, len, func);
    };
}
