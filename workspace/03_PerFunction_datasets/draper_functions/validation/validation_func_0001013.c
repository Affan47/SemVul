insertToken(const std::string &tokenStr, bool prepend)
{

    if (prepend && !this->previous())
        return;
    Token *newToken;
    if (_str.empty())
        newToken = this;
    else
        newToken = new Token(tokensBack);
    newToken->str(tokenStr);
    newToken->_linenr = _linenr;
    newToken->_fileIndex = _fileIndex;
    newToken->_progressValue = _progressValue;

    if (newToken != this) {
        if (prepend) {
             {
                newToken->previous(this->previous());
                newToken->previous()->next(newToken);
            }


            this->previous(newToken);
            newToken->next(this);
        } else {
            if (this->next()) {
                newToken->next(this->next());
                newToken->next()->previous(newToken);
            } else if (tokensBack) {
                *tokensBack = newToken;
            }
            this->next(newToken);
            newToken->previous(this);
        }
    }
}
