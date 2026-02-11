ParseLeftHandSideExpression(bool* ok) {


  Expression result = Expression::Default();
  if (peek() == i::Token::NEW) {
    result = ParseNewExpression(CHECK_OK);
  } else {
    result = ParseMemberExpression(CHECK_OK);
  }

  while (true) {
    switch (peek()) {
      case i::Token::LBRACK: {
        Consume(i::Token::LBRACK);
        ParseExpression(true, CHECK_OK);
        Expect(i::Token::RBRACK, CHECK_OK);
        if (result.IsThis()) {
          result = Expression::ThisProperty();
        } else {
          result = Expression::Default();
        }
        break;
      }

      case i::Token::LPAREN: {
        ParseArguments(CHECK_OK);
        result = Expression::Default();
        break;
      }

      case i::Token::PERIOD: {
        Consume(i::Token::PERIOD);
        ParseIdentifierName(CHECK_OK);
        if (result.IsThis()) {
          result = Expression::ThisProperty();
        } else {
          result = Expression::Default();
        }
        break;
      }

      default:
        return result;
    }
  }
}
