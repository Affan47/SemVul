getGenreName(FXint id){
  FXString name;
  try {
    GMQuery query(&db,"SELECT name FROM genres WHERE id == ?;");
    query.setParameter(0,id);
    query.execute();
    query.getResult(0,name);
    query.reset();
    }
  catch (FXCompileException &){
    return FXString::null;
    }
  catch (FXExecuteException &){
    return FXString::null;
    }
  return name;
  }
