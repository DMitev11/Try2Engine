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
        const char *kPath;
        const int kWidth;
        const int kHeight;

      protected:
        Texture(const char *path, int width, int height)
            : kPath(path), kWidth(width), kHeight(height) {}
    };
} // namespace objects