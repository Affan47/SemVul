StringToBlendFunc(const std::string& m)
{
	if (m == "GL_ONE") {
		return Q3Shader::BLEND_GL_ONE;
	}
	if (m == "GL_ZERO") {
		return Q3Shader::BLEND_GL_ZERO;
	}
	if (m == "GL_SRC_ALPHA") {
		return Q3Shader::BLEND_GL_SRC_ALPHA;
	}
	if (m == "GL_ONE_MINUS_SRC_ALPHA") {
		return Q3Shader::BLEND_GL_ONE_MINUS_SRC_ALPHA;
	}
	if (m == "GL_ONE_MINUS_DST_COLOR") {
		return Q3Shader::BLEND_GL_ONE_MINUS_DST_COLOR;
	}
	DefaultLogger::get()->error("Q3Shader: Unknown blend function: " + m);
	return Q3Shader::BLEND_NONE;
}
