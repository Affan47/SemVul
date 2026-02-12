bool isXmpType(BasicIo& iIo, bool advance)
    {


        const int32_t len = 80;
        byte buf[len];
        iIo.read(buf, xmlHdrCnt + 1);
        if (   iIo.eof()
            && 0 == strncmp(reinterpret_cast<const char*>(buf), xmlHeader, xmlHdrCnt)) {
            return true;
        }
        if (iIo.error() || iIo.eof()) {
            return false;
        }
        iIo.read(buf + xmlHdrCnt + 1, len - xmlHdrCnt - 1);
        if (iIo.error() || iIo.eof()) {
            return false;
        }

        int32_t start = 0;
        if (0 == strncmp(reinterpret_cast<const char*>(buf), "\xef\xbb\xbf", 3)) {
            start = 3;
        }
        bool rc = false;
        std::string head(reinterpret_cast<const char*>(buf + start), len - start);
        if (head.substr(0, 5)  == "<?xml") {

            for (unsigned i = 5; i < head.size(); ++i) {
                if (head[i] == '<') {
                    head = head.substr(i);
                    break;
                }
            }
        }
        if (   head.size() > 9
            && (   head.substr(0, 9)  == "<?xpacket"
                || head.substr(0, 10) == "<x:xmpmeta")) {
            rc = true;
        }
        if (!advance || !rc) {
            iIo.seek(-(len - start), BasicIo::cur);
        }
        return rc;

    }
