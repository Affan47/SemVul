tokenize(const string &str, vector<float> &tokens, const string &delimiters) {


    string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    string::size_type pos = str.find_first_of(delimiters, lastPos);

    tokens.clear();
    float f;
    while (string::npos != pos || string::npos != lastPos) {

        string temp = str.substr(lastPos, pos - lastPos);
        from_string<float> (f, temp, std::dec);
        tokens.push_back(f);

        lastPos = str.find_first_not_of(delimiters, pos);

        pos = str.find_first_of(delimiters, lastPos);
    }

}
