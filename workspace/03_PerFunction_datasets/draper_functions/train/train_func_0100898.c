CheckTable(struct GPTHeader *header) {
   uint32_t sizeOfParts, newCRC;
   GPTPart *partsToCheck;
   GPTHeader *otherHeader;
   int allOK = 0;


   if (myDisk.Seek(header->partitionEntriesLBA)) {
      partsToCheck = new GPTPart[header->numParts];
      sizeOfParts = header->numParts * header->sizeOfPartitionEntries;
      if (partsToCheck == NULL) {
         cerr << "Could not allocate memory in GPTData::CheckTable()! Terminating!\n";
         exit(1);
      }
      if (myDisk.Read(partsToCheck, sizeOfParts) != (int) sizeOfParts) {
         cerr << "Warning! Error " << errno << " reading partition table for CRC check!\n";
      } else {
         newCRC = chksum_crc32((unsigned char*) partsToCheck, sizeOfParts);
         allOK = (newCRC == header->partitionEntriesCRC);
         if (header == &mainHeader)
            otherHeader = &secondHeader;
         else
            otherHeader = &mainHeader;
         if (newCRC != otherHeader->partitionEntriesCRC) {
            cerr << "Warning! Main and backup partition tables differ! Use the 'c' and 'e' options\n"
                 << "on the recovery & transformation menu to examine the two tables.\n\n";
            allOK = 0;
         }
      }
      delete[] partsToCheck;
   }
   return allOK;
}
