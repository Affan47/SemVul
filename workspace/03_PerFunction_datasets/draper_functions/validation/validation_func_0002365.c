protobuf_AddDesc_message_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rmessage.proto\022\007message\"W\n\010envelope\022\020\n\010"
    "msg_type\030\001 \002(\t\022\020\n\010msg_size\030\002 \002(\r\022\020\n\010msg_"
    "data\030\003 \001(\014\022\013\n\003mac\030\004 \001(\014*\010\010d\020\200\200\200\200\002:\036\n\003key"
    "\022\021.message.envelope\030d \001(\014", 145);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "message.proto", &protobuf_RegisterTypes);
  envelope::default_instance_ = new envelope();
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::message::envelope::default_instance(),
    100, 12, false, false);
  envelope::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_message_2eproto);
}
