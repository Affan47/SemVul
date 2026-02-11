is_user_page(const char *zId){
  if( zId && strcmp(zId,"setup") && strcmp(zId,"anonymous") ){
    if( db_exists("SELECT 1 FROM user,wiki "
                  "WHERE user.id='%q' AND wiki.name=user.id", zId) ){
      return 1;
    }
  }
  return 0;
}
