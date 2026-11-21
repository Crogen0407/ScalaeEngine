class IGraphicModule;
class Engine
{
public:
	Engine(HWND hWnd);
	void GameLoop();
	void Render();
	void Update();

private:
	std::shared_ptr<IGraphicModule> _targetGraphicModule = nullptr;
};