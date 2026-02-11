beginOcclusionQuery()
{
    if(GLEW_VERSION_1_5 || GLEW_ARB_occlusion_query)
    {
        glBeginQueryARB(GL_SAMPLES_PASSED_ARB, mQueryID);
    }
    else if (GLEW_NV_occlusion_query)
    {
        glBeginOcclusionQueryNV(mQueryID);
    }
}
