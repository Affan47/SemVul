LoadSamples() {
        if (!pSamples) pSamples = new SampleList;
        RIFF::List* wvpl = pRIFF->GetSubList(LIST_TYPE_WVPL);
        if (wvpl) {
            unsigned long wvplFileOffset = wvpl->GetFilePos();
            RIFF::List* wave = wvpl->GetFirstSubList();
            while (wave) {
                if (wave->GetListType() == LIST_TYPE_WAVE) {
                    unsigned long waveFileOffset = wave->GetFilePos();
                    pSamples->push_back(new Sample(this, wave, waveFileOffset - wvplFileOffset));
                }
                wave = wvpl->GetNextSubList();
            }
        }
        else {
            RIFF::List* dwpl = pRIFF->GetSubList(LIST_TYPE_DWPL);
            if (dwpl) {
                unsigned long dwplFileOffset = dwpl->GetFilePos();
                RIFF::List* wave = dwpl->GetFirstSubList();
                while (wave) {
                    if (wave->GetListType() == LIST_TYPE_WAVE) {
                        unsigned long waveFileOffset = wave->GetFilePos();
                        pSamples->push_back(new Sample(this, wave, waveFileOffset - dwplFileOffset));
                    }
                    wave = dwpl->GetNextSubList();
                }
            }
        }
    }
