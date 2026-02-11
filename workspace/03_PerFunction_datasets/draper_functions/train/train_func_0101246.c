findWord(char *s, int16_t length) {
    uint32_t i;

    for(i=0; i<wordCount; ++i) {
        if(length==words[i].length && 0==uprv_memcmp(s, words[i].s, length)) {
            return words+i;
        }
    }

    return NULL;
}
