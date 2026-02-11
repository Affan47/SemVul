insertElementAt(void* obj, int32_t index, UErrorCode &status) {

    if (0 <= index && index <= count && ensureCapacity(count + 1, status)) {
        for (int32_t i=count; i>index; --i) {
            elements[i] = elements[i-1];
        }
        elements[index].pointer = obj;
        ++count;
    }

}
