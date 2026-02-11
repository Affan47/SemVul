setEnv(std::string key, const std::string env) {
    if(env.empty())return;
    if(key.empty())return;

    char*result=getenv(env.c_str());
    if(NULL==result) {
      return;
    }

    t_atom a;
    errno=0;


    long l=strtol(result, NULL, 0);
    if(0==errno) {
      SETFLOAT(&a, l);
      set(key, &a);
    }


    double d=strtod(result, NULL);
    if(0==errno) {
      SETFLOAT(&a, d);
      set(key, &a);
    }


    SETSYMBOL(&a, gensym(result));
    set(key, &a);


  }
}
