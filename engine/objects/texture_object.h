#pragma once
namespace objects {
    struct TextureSize {
        TextureSize(int w, int h) : w(w), h(h){};
        int w;
        int h;
    };
    class Texture {
      public:
        ~Texture() = default;
        const char *path;
        const int width;
        const int height;

      protected:
        Texture(const char *path, int width, int height)
            : width(width), height(height) {
            this->path = path;
        }
    };
} // namespace objects