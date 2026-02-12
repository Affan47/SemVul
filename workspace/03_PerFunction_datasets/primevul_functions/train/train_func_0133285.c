bool getBase64Row(char*, int , char*&, char*&)
    {
        CV_PARSE_ERROR_CPP("Currently, JSON parser does not support base64 data");
        return false;
    }
