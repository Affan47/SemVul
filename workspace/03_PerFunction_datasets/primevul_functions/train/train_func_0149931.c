void Parser::shift(const char *cmdA, int objNum) {
  if (inlineImg > 0) {
    if (inlineImg < 2) {
      ++inlineImg;
    } else {


      inlineImg = 0;
    }
  } else if (buf2.isCmd("ID")) {
    lexer->skipChar();
    inlineImg = 1;
  }
  buf1 = std::move(buf2);
  if (inlineImg > 0) {
    buf2.setToNull();
  } else if (buf1.isCmd(cmdA)) {
    buf2 = lexer->getObj(objNum);
  } else {
    buf2 = lexer->getObj(cmdA, objNum);
  }
}
