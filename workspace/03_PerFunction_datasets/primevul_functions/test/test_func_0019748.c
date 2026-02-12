CurlIo::CurlImpl::CurlImpl(const std::string& url, size_t blockSize):Impl(url, blockSize)
    {

        curl_ = curl_easy_init();
        if(!curl_) {
            throw Error(1, "Uable to init libcurl.");
        }


        if (blockSize_ == 0) {
            blockSize_ = protocol_ == pFtp ? 102400 : 1024;
        }

        std::string timeout = getEnv(envTIMEOUT);
        timeout_ = atol(timeout.c_str());
        if (timeout_ == 0) {
            throw Error(1, "Timeout Environmental Variable must be a positive integer.");
        }
    }
