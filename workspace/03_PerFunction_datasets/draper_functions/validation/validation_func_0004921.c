array_class_get_if_rank (MonoClass *class, guint rank)
{
	return rank ? mono_array_class_get (class, rank) :  class;
}
