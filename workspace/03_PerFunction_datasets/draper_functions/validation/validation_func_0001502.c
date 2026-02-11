removeTrailingWhitespace(string &str) {

    string::size_type first_pos = str.find_last_not_of(" \t");
    string::size_type last_pos = str.find_first_of(" \t", first_pos);
    if (last_pos != string::npos)
        str.erase(last_pos);
    return first_pos;
}
