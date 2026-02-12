Value ExpressionReplaceAll::_doEval(StringData input,
                                    StringData find,
                                    StringData replacement) const {


    if (find.size() == 0) {
        StringBuilder output;
        for (char c : input) {
            output << replacement << c;
        }
        output << replacement;
        return Value(output.stringData());
    }

    StringBuilder output;
    for (;;) {
        size_t startIndex = input.find(find);
        if (startIndex == std::string::npos) {
            output << input;
            break;
        }

        size_t endIndex = startIndex + find.size();
        output << input.substr(0, startIndex);
        output << replacement;


        input = input.substr(endIndex);
    }
    return Value(output.stringData());
}
