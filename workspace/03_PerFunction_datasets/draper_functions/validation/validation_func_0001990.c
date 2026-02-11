invertOperatorForOperandSwap(std::string s)
{
    if (s[0] == '<')
        s[0] = '>';
    else if (s[0] == '>')
        s[0] = '<';
    return s;
}
