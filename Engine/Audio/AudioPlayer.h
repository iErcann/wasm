namespace MO3D
{
    class AudioPlayer
    {
    public:
        AudioPlayer();
        static AudioPlayer &GetInstance()
        {
            static AudioPlayer reference;
            return reference;
        }
        void Initialize();
    };
    static AudioPlayer &Audio = AudioPlayer::GetInstance();
} // namespace MO3D