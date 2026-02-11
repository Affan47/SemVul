__ecereNameSpace__ecere__sys__RepeatCh(char * string, int count, char ch)
{
int c;

for(c = 0; c < count; c++)
string[c] = ch;
string[c] = (char)0;
}
