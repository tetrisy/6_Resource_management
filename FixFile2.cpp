#include <memory>

void Render()
{
    if (!isVisible()) return;
    std::unique_ptr<Texture> t(loadTexture("hero.png"));
    Draw(t.get()); 
}

// if isVisible returns t memory is never deleted