long CurlIo::CurlImpl::getFileLength()
    {
        curl_easy_reset(curl_);
        std::string response;
        curl_easy_setopt(curl_, CURLOPT_URL, path_.c_str());
        curl_easy_setopt(curl_, CURLOPT_NOBODY, 1);
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, curlWriter);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl_, CURLOPT_CONNECTTIMEOUT, timeout_);


        CURLcode res = curl_easy_perform(curl_);
        if(res != CURLE_OK) {
            throw Error(1, curl_easy_strerror(res));
        }

        long returnCode;
        curl_easy_getinfo (curl_, CURLINFO_RESPONSE_CODE, &returnCode);
        if (returnCode >= 400 || returnCode < 0) {
            throw Error(55, "Server", returnCode);
        }

        double temp;
        curl_easy_getinfo(curl_, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &temp);
        return (long) temp;
    }
