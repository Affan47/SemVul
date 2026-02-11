mono_method_can_access_method (MonoMethod *method, MonoMethod *called)
{
	int can = can_access_member (method->klass, called->klass, NULL, called->flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK);
	if (!can) {
		MonoClass *nested = method->klass->nested_in;
		while (nested) {
			can = can_access_member (nested, called->klass, NULL, called->flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK);
			if (can)
				return TRUE;
			nested = nested->nested_in;
		}
	}


	if ((called->flags & METHOD_ATTRIBUTE_VIRTUAL) && (called->flags & METHOD_ATTRIBUTE_FINAL))
		return TRUE;
	return can;
}
