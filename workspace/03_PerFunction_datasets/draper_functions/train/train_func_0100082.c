compile(const bool checkErrors)
    {
        if (mCompiled == 1)
        {
            return true;
        }


        if (isSupported())
        {

            GLenum shaderType = 0x0000;
            switch (mType)
            {
            case GPT_VERTEX_PROGRAM:
                shaderType = GL_VERTEX_SHADER_ARB;
                break;
            case GPT_FRAGMENT_PROGRAM:
                shaderType = GL_FRAGMENT_SHADER_ARB;
                break;
            case GPT_GEOMETRY_PROGRAM:
                shaderType = GL_GEOMETRY_SHADER_EXT;
                break;
            case GPT_COMPUTE_PROGRAM:
            case GPT_DOMAIN_PROGRAM:
            case GPT_HULL_PROGRAM:
                break;
            }
            mGLHandle = glCreateShaderObjectARB(shaderType);
        }


        if (!mSource.empty())
        {
            const char *source = mSource.c_str();
            glShaderSourceARB(mGLHandle, 1, &source, NULL);
        }

        if (checkErrors)
        {
            logObjectInfo("GLSL compiling: " + mName, mGLHandle);
        }

        glCompileShaderARB(mGLHandle);

        glGetObjectParameterivARB(mGLHandle, GL_OBJECT_COMPILE_STATUS_ARB, &mCompiled);
        if(checkErrors)
        {
            logObjectInfo(mCompiled ? "GLSL compiled: " : "GLSL compile log: "  + mName, mGLHandle);
        }

        return (mCompiled == 1);
    }
