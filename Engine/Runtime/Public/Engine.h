class IGraphicModule;
class Engine
{
public:
	Engine(HWND hWnd);
	void GameLoop();
	void Render();
	void Update();

private:
	IGraphicModule* _targetGraphicModule = nullptr;
};