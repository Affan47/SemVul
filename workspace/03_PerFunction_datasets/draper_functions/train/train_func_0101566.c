operator=(const Transliterator& other) {
    ID = other.ID;

    ID.getTerminatedBuffer();

    maximumContextLength = other.maximumContextLength;
    adoptFilter((other.filter == 0) ? 0 : (UnicodeFilter*) other.filter->clone());
    return *this;
}
