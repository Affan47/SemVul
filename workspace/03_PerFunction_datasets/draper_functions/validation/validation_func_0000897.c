Set(const FileAccess *s,const FileAccess::Path &cwd)
{
   if(cwd.path==0 || !strcmp(cwd.path,"~") || s->GetHostName()==0)
      return;
   xstring res;
   res.setf("%lu:",(unsigned long)time(0));
   if(!cwd.url)
   {
      res.append_url_encoded(cwd,URL_PATH_UNSAFE);
      if(!cwd.is_file && url::dir_needs_trailing_slash(s->GetProto()))
	 res.append('/');
   }
   else
      res.append(cwd.url);
   super::Add(s->GetConnectURL(s->NO_PATH|s->NO_PASSWORD),res);
   modified=true;
}
