to_tasksytyp(int32 ttyp)
{
 int32 styp;

 styp = SYM_UNKN;
 switch ((byte) ttyp) {
  case TASK: styp = SYM_TSK; break;
  case FUNCTION: styp = SYM_F; break;
  case FORK: case Begin: styp = SYM_LB; break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(styp);
}
