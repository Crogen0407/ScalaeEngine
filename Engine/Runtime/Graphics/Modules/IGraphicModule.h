class IGraphicModule
{
public:
	virtual void Initialize(HWND hwnd) abstract;
	virtual void RenderBegin() abstract;
	virtual void RenderEnd() abstract;
};