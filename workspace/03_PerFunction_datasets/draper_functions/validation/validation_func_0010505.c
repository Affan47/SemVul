matchAll(const std::string& str, std::vector<std::string>* results) {

    int offset = -1;
    if(results != 0) results->clear();
    while((offset = matchOffset(str, results, offset+1)) != -1 && offset < str.size());

    return (offset != -1);
}
