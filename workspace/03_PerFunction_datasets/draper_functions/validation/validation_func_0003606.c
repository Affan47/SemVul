hard_check(int tryhard) {
    masstree_precondition(inbufpos_ == inbuflen_);
    if (parser_.empty()) {
        inbuftotal_ += inbufpos_;
        inbufpos_ = inbuflen_ = 0;
        for (auto x : oldinbuf_)
            delete[] x;
        oldinbuf_.clear();
    } else if (inbufpos_ == inbufsz) {
        oldinbuf_.push_back(inbuf_);
        inbuf_ = new char[inbufsz];
        inbuftotal_ += inbufpos_;
        inbufpos_ = inbuflen_ = 0;
    }
    if (tryhard == 1) {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        struct timeval tv = {0, 0};
        if (select(fd + 1, &rfds, NULL, NULL, &tv) <= 0)
            return;
    } else
        kvflush(kvout);

    ssize_t r = read(fd, inbuf_ + inbufpos_, inbufsz - inbufpos_);
    if (r != -1)
        inbuflen_ += r;
}
