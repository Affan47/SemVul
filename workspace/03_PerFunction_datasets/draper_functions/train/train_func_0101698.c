L323()
{	object *old_base=vs_base;
	fixnum x;
	x=
	XWriteBitmapFile(
	object_to_fixnum(vs_base[0]),
	vs_base[1],
	object_to_fixnum(vs_base[2]),
	object_to_fixnum(vs_base[3]),
	object_to_fixnum(vs_base[4]),
	object_to_fixnum(vs_base[5]),
	object_to_fixnum(vs_base[6]));
	vs_top=(vs_base=old_base)+1;
	vs_base[0]=CMPmake_fixnum(x);
}
