GetFastFileHash(const std::string & filename)
    {
        FileHashResultPtr fileHashResultPtr;
        {
            AutoMutex lock(g_fastFileHashCache_mutex);
            FileCacheMap::iterator iter = g_fastFileHashCache.find(filename);
            if(iter != g_fastFileHashCache.end())
            {
                fileHashResultPtr = iter->second;
            }
            else
            {
                fileHashResultPtr = FileHashResultPtr(new FileHashResult);
                g_fastFileHashCache[filename] = fileHashResultPtr;
            }
        }

        std::string hash;
        {
            AutoMutex lock(fileHashResultPtr->mutex);
            if(!fileHashResultPtr->ready)
            {
                fileHashResultPtr->ready = true;
                fileHashResultPtr->hash = ComputeHash(filename);
            }

            hash = fileHashResultPtr->hash;
        }

        return hash;
    }
