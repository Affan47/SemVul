receiveMessage(PORT inPort, MESSAGE message) {
    if (inPort == IN0) {
        send(OUT0, message);
    }
    else {
        if (pImpl) {
            pImpl->receiveMessage(inPort, message);
        }
    }
}
