DisplayFrameBufferAttachments()
{
  GLint framebufferBinding;
  glGetIntegerv(vtkgl::FRAMEBUFFER_BINDING_EXT,&framebufferBinding);
  vtkGraphicErrorMacro(this->Context,"after getting FRAMEBUFFER_BINDING_EXT");
  if(framebufferBinding==0)
    {
    cout<<"Current framebuffer is bind to the system one"<<endl;
    }
  else
    {
    cout<<"Current framebuffer is bind to framebuffer object "
        <<framebufferBinding<<endl;

    GLint maxColorAttachments;
    glGetIntegerv(vtkgl::MAX_COLOR_ATTACHMENTS_EXT,&maxColorAttachments);
    vtkGraphicErrorMacro(this->Context,"after getting MAX_COLOR_ATTACHMENTS_EXT");
    int i=0;
    while(i<maxColorAttachments)
      {
      cout<<"color attachement "<<i<<":"<<endl;
      this->DisplayFrameBufferAttachment(vtkgl::COLOR_ATTACHMENT0_EXT+i);
      ++i;
      }
    cout<<"depth attachement :"<<endl;
    this->DisplayFrameBufferAttachment(vtkgl::DEPTH_ATTACHMENT_EXT);
    cout<<"stencil attachement :"<<endl;
    this->DisplayFrameBufferAttachment(vtkgl::STENCIL_ATTACHMENT_EXT);
    }
}
