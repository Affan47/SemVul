startFunctionBody(const Function *F, uintptr_t &ActualSize) {

      FreeRangeHeader* candidateBlock = FreeMemoryList;
      FreeRangeHeader* head = FreeMemoryList;
      FreeRangeHeader* iter = head->Next;

      uintptr_t largest = candidateBlock->BlockSize;


      while (iter != head) {
        if (iter->BlockSize > largest) {
          largest = iter->BlockSize;
          candidateBlock = iter;
        }
        iter = iter->Next;
      }

      largest = largest - sizeof(MemoryRangeHeader);


      if (largest < ActualSize ||
          largest <= FreeRangeHeader::getMinBlockSize()) {
        DEBUG(dbgs() << "JIT: Allocating another slab of memory for function.");
        candidateBlock = allocateNewCodeSlab((size_t)ActualSize);
      }


      CurBlock = candidateBlock;


      FreeMemoryList = candidateBlock->AllocateBlock();
      ActualSize = CurBlock->BlockSize - sizeof(MemoryRangeHeader);
      return (uint8_t *)(CurBlock + 1);
    }
