SetPos(unsigned long Where, stream_whence_t Whence) {
     #if DEBUG
     std::cout << "Chunk::SetPos(ulong)" << std::endl;
     #endif
        switch (Whence) {
            case stream_curpos:
                ulPos += Where;
                break;
            case stream_end:
                ulPos = CurrentChunkSize - 1 - Where;
                break;
            case stream_backward:
                ulPos -= Where;
                break;
            case stream_start: default:
                ulPos = Where;
                break;
        }
        if (ulPos > CurrentChunkSize) ulPos = CurrentChunkSize;
        return ulPos;
    }
