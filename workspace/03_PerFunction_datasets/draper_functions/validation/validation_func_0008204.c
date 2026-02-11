ShowRunStatus(const SMTaskRef<StatusLine>& s)
{
   if(Done())
      return;

   s->Show("%s `%s' [%s]",args->getarg(0),
      squeeze_file_name(curr,s->GetWidthDelayed()-40),
      session->CurrentStatus());
}
