append(const FXchar* s){
  if(s && s[0]){
    register FXint len=length();
    register FXint n=strlen(s);
    length(len+n);
    memcpy(str+len,s,n);
    }
  return *this;
  }
