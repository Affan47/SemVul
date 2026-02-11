ReserveSpace(int bytes) {
  Address limit = allocation_info_.limit;
  Address top = allocation_info_.top;
  if (limit - top >= bytes) return true;


  PutRestOfCurrentPageOnFreeList(TopPageOf(allocation_info_));

  Page* reserved_page = TopPageOf(allocation_info_);
  int bytes_left_to_reserve = bytes;
  while (bytes_left_to_reserve > 0) {
    if (!reserved_page->next_page()->is_valid()) {
      if (Heap::OldGenerationAllocationLimitReached()) return false;
      Expand(reserved_page);
    }
    bytes_left_to_reserve -= Page::kPageSize;
    reserved_page = reserved_page->next_page();
    if (!reserved_page->is_valid()) return false;
  }
  ASSERT(TopPageOf(allocation_info_)->next_page()->is_valid());
  TopPageOf(allocation_info_)->next_page()->InvalidateWatermark(true);
  SetAllocationInfo(&allocation_info_,
                    TopPageOf(allocation_info_)->next_page());
  return true;
}
