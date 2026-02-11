__ecereMethod___ecereNameSpace__ecere__sys__DualPipe_Write(struct __ecereNameSpace__ecere__com__Instance * this, unsigned char * buffer, unsigned int size, unsigned int count)
{
struct __ecereNameSpace__ecere__sys__DualPipe * __ecerePointer___ecereNameSpace__ecere__sys__DualPipe = (struct __ecereNameSpace__ecere__sys__DualPipe *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__DualPipe->offset) : 0);

return __ecereProp___ecereNameSpace__ecere__sys__File_Get_output(this) ? ((int (*)(struct __ecereNameSpace__ecere__com__Instance *, void *  buffer, unsigned int size, unsigned int count))__ecereClass___ecereNameSpace__ecere__sys__File->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Write])(this, buffer, size, count) : DualPipe_Write(__ecerePointer___ecereNameSpace__ecere__sys__DualPipe->dp, buffer, size, count);
}
