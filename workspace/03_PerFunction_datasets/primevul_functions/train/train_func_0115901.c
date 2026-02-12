int TimeValue::read(const std::string& buf)
    {

        int rc = 1;
        if (buf.length() < 9) {

            rc = scanTime3(buf.c_str(), "%d:%d:%d");
        }
        else {
            rc = scanTime6(buf.c_str(), "%d:%d:%d%1c%d:%d");
        }
        if (rc) {
            rc = 1;
#ifndef SUPPRESS_WARNINGS
            EXV_WARNING << Error(kerUnsupportedTimeFormat) << "\n";
#endif
        }
        return rc;
    }
