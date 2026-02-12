bool DL_Dxf::getStrippedLine(std::string& s, unsigned int size, FILE *fp, bool stripSpace) {
    if (!feof(fp)) {

        char* wholeLine = new char[size];

        char* line;

        line = fgets(wholeLine, size, fp);

        if (line!=NULL && line[0] != '\0') {


            stripWhiteSpace(&line, stripSpace);

            s = line;
            assert(size > s.length());
        }

        delete[] wholeLine;

        return true;
    } else {
        s = "";
        return false;
    }
}
