AddBinding()
{
	bindings.push_back(new FCDEffectPassBind(GetDocument()));
	SetNewChildFlag();
	return bindings.back();
}
