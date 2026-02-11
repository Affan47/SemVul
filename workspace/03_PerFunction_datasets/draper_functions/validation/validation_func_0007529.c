initialize_opengl_sync() {
    check_opengl_sync_capabilities();
    decide_opengl_sync_method();
#ifdef USE_GLES

#else
    if (g_has_nv_fence) {
        glGenFencesNV(1, &g_fence);
        CHECK_GL_ERROR_MSG("glGenFencesNV(1, &g_fence)");
    }
    else if (g_has_apple_fence) {
        glGenFencesAPPLE(1, &g_fence);
        CHECK_GL_ERROR_MSG("glGenFencesAPPLE(1, &g_fence)");
    }
#endif
}
