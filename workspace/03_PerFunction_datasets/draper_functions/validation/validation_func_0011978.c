SlowAllocateRaw(int size_in_bytes) {
  ASSERT_EQ(object_size_in_bytes_, size_in_bytes);


  Page* current_page = TopPageOf(allocation_info_);
  if (current_page->next_page()->is_valid()) {
    return AllocateInNextPage(current_page, size_in_bytes);
  }


  if (!heap()->linear_allocation()) {
    Object* result;
    MaybeObject* maybe = free_list_.Allocate();
    if (maybe->ToObject(&result)) {
      accounting_stats_.AllocateBytes(size_in_bytes);
      HeapObject* obj = HeapObject::cast(result);
      Page* p = Page::FromAddress(obj->address());

      if (obj->address() >= p->AllocationWatermark()) {


        ASSERT(obj->address() == p->AllocationWatermark());
        p->SetAllocationWatermark(obj->address() + size_in_bytes);
      }

      return obj;
    }
  }


  if (!heap()->always_allocate() &&
      heap()->OldGenerationAllocationLimitReached()) {
    return NULL;
  }


  ASSERT(!current_page->next_page()->is_valid());
  if (Expand(current_page)) {
    return AllocateInNextPage(current_page, size_in_bytes);
  }


  return NULL;
}
