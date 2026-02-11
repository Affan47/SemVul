tolua_px_ecl_Drawable_box00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GS",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  const GS* gs = ((const GS*)  tolua_tousertype(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  int w = ((int)  tolua_tonumber(tolua_S,5,0));
  int h = ((int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'box'",NULL);
#endif
  {
   self->box(*gs,x,y,w,h);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'box'.",&tolua_err);
 return 0;
#endif
}
