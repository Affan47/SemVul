wdel(const string& s)
{
    size_t i = 0;
    size_t j = s.size();
    while (i<j && s[i]==' ') i++;
    while (j>i && s[j-1] == ' ') j--;
    return s.substr(i,j-i);
}
