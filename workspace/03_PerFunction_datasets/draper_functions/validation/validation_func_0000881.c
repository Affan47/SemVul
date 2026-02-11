groupTypeSelected(int cg)
{
  switch(cg) {
  case 0: setGroupType( ProfileContext::Function ); break;
  case 1: setGroupType( ProfileContext::Object ); break;
  case 2: setGroupType( ProfileContext::File ); break;
  case 3: setGroupType( ProfileContext::Class ); break;
  case 4: setGroupType( ProfileContext::FunctionCycle ); break;
  default: break;
  }
}
