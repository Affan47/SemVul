constMultExpression() {
    INTEGER right, result ;
    result = constUnaryExpression() ;
    for (;;) {
        if (match (STAR)) {
            right = constUnaryExpression() ;
            result *= right ;
        } else if (match (SLASH)) {
            right = constUnaryExpression() ;
            result /= right ;
        } else if (match (PERCENT)) {
            right = constUnaryExpression() ;
            result %= right ;
        } else {
            return result ;
        }
    }
}
