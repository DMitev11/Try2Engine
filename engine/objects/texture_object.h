#pragma once
namespace objects
{
    class Texture
    {
      public:
        ~Texture() = default;
        const char *path;
        const int width;
        const int height;

      protected:
        Texture(const char *path, int width, int height) : width(width), height(height)
        {
            this->path = path;
        }
    };
} // namespace objects