FuncSET_PRINT_FORMATTING_STDOUT(Obj self, Obj val) {
  if (val == False)
    (OutputFiles+1)->format = 0;
  else
    (OutputFiles+1)->format = 1;
  return val;
}
