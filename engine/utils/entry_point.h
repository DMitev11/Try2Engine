namespace utils {

    class Entry {
      public:
        Entry() = default;
        virtual ~Entry() = default;

        virtual void Run() = 0;
    };

    extern Entry *createEntryPoint();
} // namespace utils