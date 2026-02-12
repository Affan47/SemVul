void appendInvalidStringElement(const char* fieldName, BufBuilder* bb) {

        bb->appendChar(String);
        bb->appendStr(fieldName, true);
        bb->appendNum(4);
        bb->appendStr("asdf", false);
    }
