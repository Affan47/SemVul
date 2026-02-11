peek_forwarding_input_stream(InputStream * inp) {
    ForwardingInputStream * buf = (ForwardingInputStream *)((char *)inp - offsetof(ForwardingInputStream, fwd));
    return peek_stream(buf->inp);
}
