DeleteByLocation(uint64_t start64, uint64_t length64) {
   uint32_t start32, length32;
   int i, deleted = 0;

   if ((start64 < UINT32_MAX) && (length64 < UINT32_MAX)) {
      start32 = (uint32_t) start64;
      length32 = (uint32_t) length64;
      for (i = 0; i < MAX_MBR_PARTS; i++) {
         if ((partitions[i].GetType() != 0xEE) && (partitions[i].GetStartLBA() == start32)
             && (partitions[i].GetLengthLBA() == length32)) {
            DeletePartition(i);
         if (state == hybrid)
            OptimizeEESize();
         deleted = 1;
         }
      }
   }
   return deleted;
}
