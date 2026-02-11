print(const char*prefix)const
{
int i= 0;
for(const_seqit it= classes.begin();
it!=classes.end();
++it,i++){
printf("%sclass %d: ",prefix,i);
(*it).print("");
}
}
