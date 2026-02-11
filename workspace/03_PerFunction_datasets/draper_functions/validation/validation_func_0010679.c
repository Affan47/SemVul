MakePart(int num, uint64_t start, uint64_t length, int type, int bootable) {
   if ((num >= 0) && (num < MAX_MBR_PARTS) && (start <= UINT32_MAX) && (length <= UINT32_MAX)) {
      partitions[num].Empty();
      partitions[num].SetType(type);
      partitions[num].SetLocation(start, length);
      if (num < 4)
         partitions[num].SetInclusion(PRIMARY);
      else
         partitions[num].SetInclusion(LOGICAL);
      SetPartBootable(num, bootable);
   }
}
