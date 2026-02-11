visitVAArgInst(VAArgInst &I) {
  Out << "va_arg(*(va_list*)";
  writeOperand(I.getOperand(0));
  Out << ", ";
  printType(Out, I.getType());
  Out << ");\n ";
}
