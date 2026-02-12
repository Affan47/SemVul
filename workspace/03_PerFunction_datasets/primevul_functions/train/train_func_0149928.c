void Parser::shift(int objNum) {
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
  if (inlineImg > 0)
    buf2.setToNull();
  else {
    buf2 = lexer->getObj(objNum);
  }
}
