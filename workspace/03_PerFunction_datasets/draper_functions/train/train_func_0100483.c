__ecereMethod___ecereNameSpace__ecere__sys__File_GetDouble(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__sys__File * __ecerePointer___ecereNameSpace__ecere__sys__File = (struct __ecereNameSpace__ecere__sys__File *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__File->offset) : 0);
char string[32];

__ecereMethod___ecereNameSpace__ecere__sys__File_GetString(this, string, sizeof string);
return __ecereNameSpace__ecere__sys__FloatFromString(string);
}
