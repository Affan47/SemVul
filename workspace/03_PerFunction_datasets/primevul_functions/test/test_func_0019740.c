CurlIo::CurlImpl::CurlImpl(const std::wstring& wurl, size_t blockSize):Impl(wurl, blockSize)
    {
        std::string url;
        url.assign(wurl.begin(), wurl.end());
        path_ = url;


        curl_ = curl_easy_init();
        if(!curl_) {
            throw Error(1, "Uable to init libcurl.");
        }


        if (blockSize_ == 0) {
            blockSize_ = protocol_ == pFtp ? 102400 : 1024;
        }
    }
