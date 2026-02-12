void js_rot4(js_State *J)
{

	js_Value tmp = STACK[TOP-1];
	STACK[TOP-1] = STACK[TOP-2];
	STACK[TOP-2] = STACK[TOP-3];
	STACK[TOP-3] = STACK[TOP-4];
	STACK[TOP-4] = tmp;
}
