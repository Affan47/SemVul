go_component_render (GOComponent *component, cairo_t *cr,
			double width, double height)
{
	GOComponentClass *klass;

	g_return_if_fail (GO_IS_COMPONENT (component));

	klass = GO_COMPONENT_GET_CLASS(component);
	if (klass->render)
		klass->render (component, cr, width, height);
}
