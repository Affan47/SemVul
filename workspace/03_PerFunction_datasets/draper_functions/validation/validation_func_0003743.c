VisitPointers(Object** start, Object** end) {
    for (Object** p = start; p < end; p++) {
      StaticPointersToNewGenUpdatingVisitor::VisitPointer(heap_, p);
    }
  }
