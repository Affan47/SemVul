parseFile(std::istream &istr)
{

    std::string filedata;
    std::string line;
    while (std::getline(istr, line))
        filedata += line + "\n";
    std::replace(filedata.begin(), filedata.end(), '\r', '\n');


    std::istringstream istr2(filedata);
    while (std::getline(istr2, line)) {

        if (line.empty())
            continue;


        if (line.length() >= 2 && line[0] == '/' && line[1] == '/')
            continue;

        const std::string errmsg(addSuppressionLine(line));
        if (!errmsg.empty())
            return errmsg;
    }

    return "";
}
