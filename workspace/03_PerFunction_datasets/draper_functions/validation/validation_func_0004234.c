destroyRenderWindow(const String& name)
    {

        RenderTarget* pWin = detachRenderTarget(name);
        OgreAssert(pWin, "unknown RenderWindow name");

        GLContext *windowContext = 0;
        pWin->getCustomAttribute(GLRenderTexture::CustomAttributeString_GLCONTEXT, &windowContext);


        assert( windowContext );

        bool bFound = false;

        DepthBufferMap::iterator itMap = mDepthBufferPool.begin();
        DepthBufferMap::iterator enMap = mDepthBufferPool.end();

        while( itMap != enMap && !bFound )
        {
            DepthBufferVec::iterator itor = itMap->second.begin();
            DepthBufferVec::iterator end  = itMap->second.end();

            while( itor != end )
            {


                GLDepthBuffer *depthBuffer = static_cast<GLDepthBuffer*>(*itor);
                GLContext *glContext = depthBuffer->getGLContext();

                if( glContext == windowContext &&
                    (depthBuffer->getDepthBuffer() || depthBuffer->getStencilBuffer()) )
                {
                    bFound = true;

                    delete *itor;
                    itMap->second.erase( itor );
                    break;
                }
                ++itor;
            }

            ++itMap;
        }

        delete pWin;
    }
