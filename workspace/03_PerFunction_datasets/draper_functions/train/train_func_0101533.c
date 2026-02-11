Expand(Page* last_page) {
  ASSERT(max_capacity_ % Page::kObjectAreaSize == 0);
  ASSERT(Capacity() % Page::kObjectAreaSize == 0);

  if (Capacity() == max_capacity_) return false;

  ASSERT(Capacity() < max_capacity_);

  ASSERT(last_page->is_valid() && !last_page->next_page()->is_valid());

  int available_pages =
      static_cast<int>((max_capacity_ - Capacity()) / Page::kObjectAreaSize);


  if (available_pages < MemoryAllocator::kPagesPerChunk) return false;

  int desired_pages = Min(available_pages, MemoryAllocator::kPagesPerChunk);
  Page* p = heap()->isolate()->memory_allocator()->AllocatePages(
      desired_pages, &desired_pages, this);
  if (!p->is_valid()) return false;

  accounting_stats_.ExpandSpace(desired_pages * Page::kObjectAreaSize);
  ASSERT(Capacity() <= max_capacity_);

  heap()->isolate()->memory_allocator()->SetNextPage(last_page, p);


  while (p->is_valid()) {
    p->SetRegionMarks(Page::kAllRegionsCleanMarks);
    last_page_ = p;
    p = p->next_page();
  }

  return true;
}
