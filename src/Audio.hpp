#ifndef OPENALSOFT_AUDIO_HPP_
#define OPENALSOFT_AUDIO_HPP_

#include "audio/IAudio.hpp"

namespace ice_engine
{
namespace audio
{
namespace openalsoft
{

class Audio : public IAudio
{
public:
    Audio(std::vector<uint8> buffer, int frequency, uint8 channels, uint16 bitsPerSample, int32 format)
    :
    buffer_(buffer), frequency_(frequency), channels_(channels), bitsPerSample_(bitsPerSample), format_(format)
    {

    }

    ~Audio() override = default;

    const std::vector<uint8>& data() const override
    {
        return buffer_;
    }

    uint32 length() const override
    {
        return buffer_.size();
    }

    uint32 frequency() const override
    {
        return frequency_;
    }

    uint8 channels() const override
    {
        return channels_;
    }

    uint16 bitsPerSample() const override
    {
        return bitsPerSample_;
    }

    int32 format() const override
    {
        return format_;
    }

private:
    std::vector<uint8> buffer_;
    int frequency_ = 0;
    uint8 channels_ = 0;
    uint16 bitsPerSample_ = 0;
    int32 format_ = Format::FORMAT_UNKNOWN;
};

}
}
}

#endif //OPENALSOFT_AUDIO_HPP_
