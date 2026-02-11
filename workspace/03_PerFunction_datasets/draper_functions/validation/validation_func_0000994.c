UArray_isUppercase(UArray *self)
{
	UARRAY_INTFOREACH(self, i, v, if(v != toupper(v)) return 0);
	return 1;
}
