splitTokComment(char **tok, char **commentP)
{
    char *num = strchr(*tok, '#');

    if (num) {
        num[0] = 0;
        *commentP = shortenString(num+1);
    }
    else {
        *commentP = 0;
    }

    *tok = shortenString(*tok);
}
