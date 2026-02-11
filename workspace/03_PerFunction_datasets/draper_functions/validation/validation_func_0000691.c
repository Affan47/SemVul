operator=(const fxStackBuffer& other)
{
    if (&other != this) {
        u_int size = other.end - other.base;
        u_int len = other.getLength();
        if (base != buf) free(base);
        base = (size > sizeof(buf)) ? (char*) malloc(size) : &buf[0];
        end = base + size;
        next = base + len;
        memcpy(base, other.base, len);
   }
   return *this;
}
