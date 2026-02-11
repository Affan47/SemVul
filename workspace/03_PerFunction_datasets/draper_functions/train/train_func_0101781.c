read_rules(const string &infile)
  {
    ifstream ifs, ifs1, *ifsP;
    vector<string> vs;
    char buffer[BUFF_SIZE];
    char tmp_str[BUFF_SIZE];
    string patty_dir;
    OBSmartsPattern *sp;

    ifs.open(infile.c_str());
    ifsP= &ifs;
    if (!ifs)
      {
        if (getenv("BABEL_DATADIR") == NULL)
          {
            stringstream errorMsg;
            errorMsg << "The BABEL_DATADIR environment variable is not defined" << endl;
            errorMsg << "Please define it so the program can find " << infile << endl;
            obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);

          }
        else
          patty_dir = getenv("BABEL_DATADIR");
        patty_dir += FILE_SEP_CHAR;
        patty_dir += infile;
        ifs1.open(patty_dir.c_str());
        ifsP= &ifs1;


      }

    if (!ifsP)
      {
        stringstream errorMsg;
        errorMsg << "Could not open " << patty_dir << endl;
        obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);

      }
    while (ifsP->getline(buffer,BUFF_SIZE))
      {
        if (buffer[0] != '#')
          {
            tokenize(vs,buffer," \t\n");
            if (vs.size() >= 2)
              {
                strncpy(tmp_str,vs[0].c_str(), sizeof(tmp_str) - 1);
                tmp_str[sizeof(tmp_str) - 1] = '\0';
                sp = new OBSmartsPattern;
                sp->Init(tmp_str);
                _sp.push_back(sp);
                smarts.push_back(vs[0]);
                typ.push_back(vs[1]);
              }
          }
      }
  }
