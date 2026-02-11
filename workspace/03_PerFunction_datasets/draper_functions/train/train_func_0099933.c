Do()
{
   if(!c)
      return STALL;
   if(!fg_data)
      fg_data=c->GetFgData(fg);
   if(done)
      return STALL;
   if(c->Error())
   {
      const char *error=c->ErrorText();
      const char *name=GetDispName();
      if(!strstr(error,name))
	 error=xstring::cat(name,": ",error,NULL);
      eprintf("%s: %s\n",op.get(),error);
      done=true;
      return MOVED;
   }
   if(c->Done())
   {
      done=true;
      return MOVED;
   }
   if(!c->WriteAllowed() && c->WritePending())
   {
      if(no_status_on_write || clear_status_on_write)
	 ClearStatus();
      if(no_status_on_write)
	 NoStatus();

      c->AllowWrite();
      return MOVED;
   }
   return STALL;
}
