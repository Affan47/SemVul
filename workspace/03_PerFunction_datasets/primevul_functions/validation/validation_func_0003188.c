auto NativeModuleHandle::Create(class ContextHandle& context_handle) -> Local<Value> {


	auto context = context_handle.GetContext();
	return ThreePhaseTask::Run<async, CreateRunner>(*context.GetIsolateHolder(), context, module);
}
