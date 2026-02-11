initialize_pool(void* pool, size_t sz, size_t unit) {
    char* p = reinterpret_cast<char*>(pool);
    void** nextptr = reinterpret_cast<void**>(p);
    for (size_t off = unit; off + unit <= sz; off += unit) {
        *nextptr = p + off;
        nextptr = reinterpret_cast<void**>(p + off);
    }
    *nextptr = 0;
}
