MtQueueClass_ALLOCATE(ScmClass *klass, ScmObj initargs)
{

#line 158 "./queue.scm"
{ScmObj ml=Scm_GetKeyword(scm__rc.d1796[2],initargs,SCM_FALSE);
return (makemtq(klass,((SCM_INTP(ml))?(SCM_INT_VALUE(ml)):(-1))));}
}
