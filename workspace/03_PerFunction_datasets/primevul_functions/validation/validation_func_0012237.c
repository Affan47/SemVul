Value ExpressionReplaceOne::_doEval(StringData input,
                                    StringData find,
                                    StringData replacement) const {
    size_t startIndex = input.find(find);
    if (startIndex == std::string::npos) {
        return Value(StringData(input));
    }


    size_t endIndex = startIndex + find.size();
    StringBuilder output;
    output << input.substr(0, startIndex);
    output << replacement;
    output << input.substr(endIndex);
    return Value(output.stringData());
}
