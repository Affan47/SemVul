nv10_emit_material_shininess(struct gl_context *ctx, int emit)
{
	struct nouveau_pushbuf *push = context_push(ctx);
	float (*mat)[4] = ctx->Light.Material.Attrib;
	float k[6];

	nv10_get_shininess_coeff(
		CLAMP(mat[MAT_ATTRIB_FRONT_SHININESS][0], 0, 1024),
		k);

	BEGIN_NV04(push, NV10_3D(MATERIAL_SHININESS(0)), 6);
	PUSH_DATAp(push, k, 6);
}
