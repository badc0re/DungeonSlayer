#include "debugsystem.hpp"

#include "core.hpp"

void PositionDebug()
{
    if (Position::hasDebugDraw)
    {
        auto cameraView = registry.view<Camera>();
        auto &activeCamera = cameraView.get(*cameraView.begin());
        auto view = registry.view<Position>();

        view.each([activeCamera](const auto &pos) {
            sdl::Graphics::SetDrawColor(255, 0, 0, SDL_ALPHA_OPAQUE);

            auto position = activeCamera.FromWorldToScreenView(pos.position);
            sdl::Graphics::DrawLineToLayer(5, position.x(), position.y(), position.x() + 20, position.y());

            sdl::Graphics::SetDrawColor(0, 255, 0, SDL_ALPHA_OPAQUE);
            sdl::Graphics::DrawLineToLayer(5, position.x(), position.y(), position.x(), position.y() - 20);
            sdl::Graphics::ResetDrawColor();
        });
    }
}

void CameraUpdateDebug()
{
    if (!CameraData::isFollowing)
    {
        auto cameraView = registry.view<Camera>();
        auto &activeCamera = cameraView.get(*cameraView.begin());
        auto event = sdl::Events::Event();
        if (event.key.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                activeCamera.position.Set(activeCamera.position.x(),
                                          activeCamera.position.y() + activeCamera.viewRadius.y() / 10);
                break;
            case SDLK_DOWN:
                activeCamera.position.Set(activeCamera.position.x(),
                                          activeCamera.position.y() - activeCamera.viewRadius.y() / 10);
                break;
            case SDLK_LEFT:
                activeCamera.position.Set(activeCamera.position.x() - activeCamera.viewRadius.x() / 10,
                                          activeCamera.position.y());
                break;
            case SDLK_RIGHT:
                activeCamera.position.Set(activeCamera.position.x() + activeCamera.viewRadius.x() / 10,
                                          activeCamera.position.y());
                break;
            }
        }
    }
}
