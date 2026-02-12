bool IsValidOpName(StringPiece sp) {
  using ::tensorflow::strings::Scanner;

  Scanner scanner(sp);
  scanner.One(Scanner::UPPERLETTER).Any(Scanner::LETTER_DIGIT_UNDERSCORE);

  while (true) {
    if (!scanner.GetResult())
      return false;
    if (scanner.empty())
      return true;


    scanner.One(Scanner::RANGLE)
        .One(Scanner::UPPERLETTER)
        .Any(Scanner::LETTER_DIGIT_UNDERSCORE);
  }
}
