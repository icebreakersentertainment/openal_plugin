#include "OpenAlSoft.hpp"

#include <AL/alext.h>
#include <Audioclient.h>

#include <SDL_audio.h>

#include "Audio.hpp"

namespace ice_engine
{
namespace audio
{
namespace openalsoft
{

namespace
{
int32 convertFromSdlFormat(const SDL_AudioFormat format)
{
    switch (format)
    {
        case AUDIO_S8:
            return audio::IAudio::FORMAT_AUDIO_S8;

        case AUDIO_U8:
            return audio::IAudio::FORMAT_AUDIO_U8;


        case AUDIO_S16LSB:
            return audio::IAudio::FORMAT_AUDIO_S16LSB;

        case AUDIO_S16MSB:
            return audio::IAudio::FORMAT_AUDIO_S16MSB;

//        case AUDIO_S16SYS:
//			return audio::IAudio::FORMAT_AUDIO_S16SYS;

//        case AUDIO_S16:
//			return audio::IAudio::FORMAT_AUDIO_S16;


        case AUDIO_U16LSB:
            return audio::IAudio::FORMAT_AUDIO_U16LSB;

        case AUDIO_U16MSB:
            return audio::IAudio::FORMAT_AUDIO_U16MSB;

//        case AUDIO_U16SYS:
//			return audio::IAudio::FORMAT_AUDIO_U16SYS;
//
//        case AUDIO_U16:
//			return audio::IAudio::FORMAT_AUDIO_U16;


        case AUDIO_S32LSB:
            return audio::IAudio::FORMAT_AUDIO_S32LSB;

        case AUDIO_S32MSB:
            return audio::IAudio::FORMAT_AUDIO_S32MSB;

//        case AUDIO_S32SYS:
//			return audio::IAudio::FORMAT_AUDIO_S32SYS;
//
//        case AUDIO_S32:
//			return audio::IAudio::FORMAT_AUDIO_S32;


        case AUDIO_F32LSB:
            return audio::IAudio::FORMAT_AUDIO_F32LSB;

        case AUDIO_F32MSB:
            return audio::IAudio::FORMAT_AUDIO_F32MSB;

//        case AUDIO_F32SYS:
//			return audio::IAudio::FORMAT_AUDIO_F32SYS;
//
//        case AUDIO_F32:
//            return audio::IAudio::FORMAT_AUDIO_F32;

        default:
            return audio::IAudio::FORMAT_UNKNOWN;
    }
}

SDL_AudioFormat convertToSdlFormat(const int32 format)
{
    switch (format)
    {
        case audio::IAudio::FORMAT_AUDIO_S8:
            return AUDIO_S8;

        case audio::IAudio::FORMAT_AUDIO_U8:
            return AUDIO_U8;


        case audio::IAudio::FORMAT_AUDIO_S16LSB:
            return AUDIO_S16LSB;

        case audio::IAudio::FORMAT_AUDIO_S16MSB:
            return AUDIO_S16MSB;

//        case audio::IAudio::FORMAT_AUDIO_S16SYS:
//			return AUDIO_S16SYS;

//        case audio::IAudio::FORMAT_AUDIO_S16:
//			return AUDIO_S16;


        case audio::IAudio::FORMAT_AUDIO_U16LSB:
            return AUDIO_U16LSB;

        case audio::IAudio::FORMAT_AUDIO_U16MSB:
            return AUDIO_U16MSB;

//        case audio::IAudio::FORMAT_AUDIO_U16SYS:
//			return AUDIO_U16SYS;
//
//        case audio::IAudio::FORMAT_AUDIO_U16:
//			return AUDIO_U16;


        case audio::IAudio::FORMAT_AUDIO_S32LSB:
            return AUDIO_S32LSB;

        case audio::IAudio::FORMAT_AUDIO_S32MSB:
            return AUDIO_S32MSB;

//        case audio::IAudio::FORMAT_AUDIO_S32SYS:
//			return AUDIO_S32SYS;
//
//        case audio::IAudio::FORMAT_AUDIO_S32:
//			return AUDIO_S32;


        case audio::IAudio::FORMAT_AUDIO_F32LSB:
            return AUDIO_F32LSB;

        case audio::IAudio::FORMAT_AUDIO_F32MSB:
            return AUDIO_F32MSB;

//        case audio::IAudio::FORMAT_AUDIO_F32SYS:
//			return AUDIO_F32SYS;
//
//        case audio::IAudio::FORMAT_AUDIO_F32:
//            return AUDIO_F32;

        default:
            return audio::IAudio::FORMAT_UNKNOWN;
    }
}

Audio createConvertedAudio(const IAudio& audio)
{
    SDL_AudioFormat sdlFormat = 0;
    if (audio.format() == audio::IAudio::FORMAT_AUDIO_S32LSB)
    {
        sdlFormat = AUDIO_F32LSB;
    }
    else if (audio.format() == audio::IAudio::FORMAT_AUDIO_S32SYS)
    {
        sdlFormat = AUDIO_F32SYS;
    }
    else if (audio.format() == audio::IAudio::FORMAT_AUDIO_S32)
    {
        sdlFormat = AUDIO_F32;
    }

    SDL_AudioCVT cvt;

    try
    {
        SDL_BuildAudioCVT(&cvt, convertToSdlFormat(audio.format()), audio.channels(), audio.frequency(), sdlFormat, audio.channels(), audio.frequency());

        cvt.len = audio.length();
        cvt.buf = (Uint8*) SDL_malloc(cvt.len * cvt.len_mult);
        memcpy(cvt.buf, audio.data().data(), audio.length());

        SDL_ConvertAudio(&cvt);

        std::vector<uint8> buffer(cvt.buf, cvt.buf + cvt.len_cvt);

        SDL_free(cvt.buf);

        return Audio(std::move(buffer), audio.frequency(), audio.channels(), SDL_AUDIO_BITSIZE(sdlFormat), convertFromSdlFormat(sdlFormat));
    }
    catch (const std::exception& e)
    {
        if (cvt.buf != nullptr) SDL_free(cvt.buf);

        throw e;
    }
}

bool isSupportedFormat(const int32 format)
{
    switch (format)
    {
        case IAudio::FORMAT_AUDIO_S8:
        case IAudio::FORMAT_AUDIO_U8:

        case IAudio::FORMAT_AUDIO_S16LSB:
        case IAudio::FORMAT_AUDIO_S16MSB:
        case IAudio::FORMAT_AUDIO_S16SYS:
        case IAudio::FORMAT_AUDIO_S16:

        case IAudio::FORMAT_AUDIO_U16LSB:
        case IAudio::FORMAT_AUDIO_U16MSB:
        case IAudio::FORMAT_AUDIO_U16SYS:
        case IAudio::FORMAT_AUDIO_U16:

        case IAudio::FORMAT_AUDIO_F32LSB:
        case IAudio::FORMAT_AUDIO_F32MSB:
        case IAudio::FORMAT_AUDIO_F32SYS:
        case IAudio::FORMAT_AUDIO_F32:
            return true;

        default:
            return false;
    }
}

ALenum getFormat(const int32 format, const uint32 frequency, const uint16 bitsPerSample, const uint8 channels)
{
    switch (format)
    {
        case IAudio::FORMAT_AUDIO_S8:
            return AL_FORMAT_MONO8;

        case IAudio::FORMAT_AUDIO_U8:
            return AL_FORMAT_MONO8;

//        case AUDIO_U8:
//            return FORMAT_AUDIO_U8;


//        case AUDIO_S16LSB:
//            return FORMAT_AUDIO_S16LSB;
//
//        case AUDIO_S16MSB:
//            return FORMAT_AUDIO_S16MSB;
//
//        case AUDIO_S16SYS:
//            return FORMAT_AUDIO_S16SYS;

        case IAudio::FORMAT_AUDIO_S16LSB:
        case IAudio::FORMAT_AUDIO_S16SYS:
        case IAudio::FORMAT_AUDIO_S16:
            if (channels == 1)
            {
                return AL_FORMAT_MONO16;
            }
            else
            {
                return AL_FORMAT_STEREO16;
            }


//        case AUDIO_U16LSB:
//            return FORMAT_AUDIO_U16LSB;
//
//        case AUDIO_U16MSB:
//            return FORMAT_AUDIO_U16MSB;
//
//        case AUDIO_U16SYS:
//            return FORMAT_AUDIO_U16SYS;

        case IAudio::FORMAT_AUDIO_U16:
            return AL_FORMAT_MONO16;


//        case AUDIO_S32LSB:
//            return FORMAT_AUDIO_S32LSB;
//
//        case AUDIO_S32MSB:
//            return FORMAT_AUDIO_S32MSB;
//
//        case AUDIO_S32SYS:
//            return FORMAT_AUDIO_S32SYS;

//        case IAudio::FORMAT_AUDIO_S32LSB:
//        case IAudio::FORMAT_AUDIO_S32SYS:
//        case IAudio::FORMAT_AUDIO_S32:
//            return AL_FORMAT_MONO_IMA4;

//
//        case AUDIO_F32LSB:
//            return FORMAT_AUDIO_F32LSB;
//
//        case AUDIO_F32MSB:
//            return FORMAT_AUDIO_F32MSB;
//
//        case AUDIO_F32SYS:
//            return FORMAT_AUDIO_F32SYS;

        case IAudio::FORMAT_AUDIO_F32LSB:
        case IAudio::FORMAT_AUDIO_F32SYS:
        case IAudio::FORMAT_AUDIO_F32:
            if (channels == 1)
            {
                return AL_FORMAT_MONO_FLOAT32;
            }
            else
            {
                return AL_FORMAT_STEREO_FLOAT32;
            }


        default:
            return 0;
    }
}
}

ALuint source = 0;
ALuint buffer = 0;

OpenAlSoft::OpenAlSoft(utilities::Properties* properties, fs::IFileSystem* fileSystem, logger::ILogger* logger)
	:
	properties_(properties),
	fileSystem_(fileSystem),
	logger_(logger)
{
    if (alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT") == AL_TRUE)
    {
        std::string availableDeviceNames;

        if (alcIsExtensionPresent(nullptr, "ALC_ENUMERATE_ALL_EXT") == AL_TRUE)
        {
            availableDeviceNames = std::string(alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER));
        }
        else
        {
            availableDeviceNames = std::string(alcGetString(nullptr, ALC_DEVICE_SPECIFIER));
        }

        LOG_INFO(logger_, "Available OpenAL device(s): %s", availableDeviceNames);
    }
    else
    {
        LOG_WARN(logger_, "OpenAL enumeration not supported");
    }

    const auto defaultDeviceName = std::string(alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER));
    const auto deviceName = properties_->getStringValue("audio.deviceName", defaultDeviceName);

    LOG_INFO(logger_, "Initializing OpenAL device: %s", deviceName);

	device_ = alcOpenDevice(deviceName.c_str());
	
	if (!device_)
	{
		throw std::runtime_error("Unable to initialize OpenAL");
	}
	
	context_ = alcCreateContext(device_, nullptr);
	
	if (!context_)
	{
		throw std::runtime_error("Unable to create OpenAL context");
	}
	
	{
		auto result = alcMakeContextCurrent(context_);
		
		if (!result)
		{
			throw std::runtime_error("Unable to make OpenAL context current");
		}
	}
	
	ASSERT_AL_ERROR(__FILE__, __LINE__);

    ALCint frequency;
    alcGetIntegerv(device_, ALC_FREQUENCY, 1, &frequency);
    LOG_INFO(logger_, "OpenAL mixer frequency: %s hz", frequency);

    ALCint refreshRate;
    alcGetIntegerv(device_, ALC_REFRESH, 1, &refreshRate);
    LOG_INFO(logger_, "OpenAL refresh rate: %s hz", frequency / refreshRate);

    ALCint monoSources;
    alcGetIntegerv(device_, ALC_MONO_SOURCES, 1, &monoSources);

    ALCint stereoSources;
    alcGetIntegerv(device_, ALC_STEREO_SOURCES, 1, &stereoSources);

    if (!alcGetError(device_))
    {
        LOG_INFO(logger_, "OpenAL supported mono sources: %s", monoSources);
        LOG_INFO(logger_, "OpenAL supported stereo sources: %s", stereoSources);
    }

    ALCint majorVersion;
    alcGetIntegerv(device_, ALC_MAJOR_VERSION, 1, &majorVersion);

    ALCint minorVersion;
    alcGetIntegerv(device_, ALC_MINOR_VERSION, 1, &minorVersion);

    LOG_INFO(logger_, "OpenAL ALC version: %s.%s", majorVersion, minorVersion);

    const auto alcExtensions = std::string(alcGetString(device_, ALC_EXTENSIONS));
    LOG_INFO(logger_, "OpenAL ALC extensions: %s", alcExtensions);

    const auto vendorCharStar = alGetString(AL_VENDOR);
    const auto vendor = std::string(vendorCharStar != nullptr ? vendorCharStar : "");
    {
        const auto error = alGetError();
        if (error == AL_NO_ERROR)
        {
            LOG_INFO(logger_, "OpenAL vendor: %s", vendor);
        } else
        {
            LOG_WARN(logger_, "OpenAL error while getting vendor: %s: %s", error, alGetString(error));
        }
    }

    const auto rendererCharStar = alGetString(AL_RENDERER);
    const auto renderer = std::string(rendererCharStar != nullptr ? rendererCharStar : "");
    {
        const auto error = alGetError();
        if (error == AL_NO_ERROR)
        {
            LOG_INFO(logger_, "OpenAL renderer: %s", renderer);
        } else
        {
            LOG_WARN(logger_, "OpenAL error while getting renderer: %s: %s", error, alGetString(error));
        }
    }

    const auto versionCharStar = alGetString(AL_VERSION);
    const auto version = std::string(versionCharStar != nullptr ? versionCharStar : "");
    {
        const auto error = alGetError();
        if (error == AL_NO_ERROR)
        {
            LOG_INFO(logger_, "OpenAL version: %s", version);
        } else
        {
            LOG_WARN(logger_, "OpenAL error while getting version: %s: %s", error, alGetString(error));
        }
    }

    const auto extensionsCharStar = alGetString(AL_EXTENSIONS);
    const auto extensions = std::string(extensionsCharStar != nullptr ? extensionsCharStar : "");
    {
        const auto error = alGetError();
        if (error == AL_NO_ERROR)
        {
            LOG_INFO(logger_, "OpenAL extensions: %s", extensions);
        } else
        {
            LOG_WARN(logger_, "OpenAL error while getting extensions: %s: %s", error, alGetString(error));
        }
    }

//	const std::vector<std::string> extensions = {"ALC_EXT_capture"};
//
//	for (const auto& extension : extensions)
//    {
//        const auto result = alcIsExtensionPresent(device_, extension.c_str());
//
//        LOG_INFO(logger_, "OpenAL extension '%s' present: %s", extension, result);
//    }

	/*
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListenerfv(AL_ORIENTATION, listenerOri);
	
	ASSERT_AL_ERROR(__FILE__, __LINE__);
	
	// Test source
	alGenSources((ALuint)1, &source);
	// check for errors
	
	alSourcef(source, AL_PITCH, 1);
	// check for errors
	alSourcef(source, AL_GAIN, 1);
	// check for errors
	alSource3f(source, AL_POSITION, 0, 0, 0);
	// check for errors
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	// check for errors
	alSourcei(source, AL_LOOPING, AL_FALSE);
	// check for errros
	
	ASSERT_AL_ERROR(__FILE__, __LINE__);
	
	alGenBuffers((ALuint)1, &buffer);
	
	ASSERT_AL_ERROR(__FILE__, __LINE__);
	
	auto wav = loadWav("C:\\Users\\jarrett\\projects\\icebreakersentertainment\\dark_horizon\\assets\\sounds\\0614.wav");
	
	std::cout << "Device: " << alcGetString(device_, ALC_DEVICE_SPECIFIER) << std::endl;
	std::cout << wav->length << " " << wav->frequency << " ch:" << std::to_string(wav->channels) << " sa:" << wav->bitsPerSample << std::endl;
	alBufferData(buffer, AL_FORMAT_MONO16, wav->buffer, wav->length, wav->frequency);
	
	ASSERT_AL_ERROR(__FILE__, __LINE__);
	
	alSourcei(source, AL_BUFFER, buffer);
	ASSERT_AL_ERROR(__FILE__, __LINE__);
	
	alSourcePlay(source);
	
	ASSERT_AL_ERROR(__FILE__, __LINE__);
	*/
}

OpenAlSoft::~OpenAlSoft()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context_);
	alcCloseDevice(device_);
}

AudioSceneHandle OpenAlSoft::createAudioScene()
{
	return audioSceneHandles_.create();
}

void OpenAlSoft::destroyAudioScene(const AudioSceneHandle& audioSceneHandle)
{
	
}

void OpenAlSoft::tick(const AudioSceneHandle audioSceneHandle, const float32 delta)
{

}

void OpenAlSoft::beginRender()
{
	
}

void OpenAlSoft::render(const AudioSceneHandle& audioSceneHandle)
{
	auto& audioScene = audioSceneHandles_[audioSceneHandle];
	
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListenerfv(AL_ORIENTATION, listenerOri);

	ASSERT_AL_ERROR(__FILE__, __LINE__);
	
	std::vector<SoundSourceHandle> stopped;
	
	for (auto it = audioScene.soundSources.begin(); it != audioScene.soundSources.end(); it++)
	{
		ALint value = 0;
		alGetSourcei(it->source, AL_SOURCE_STATE, &value);
        ASSERT_AL_ERROR(__FILE__, __LINE__);
		
		if (value == AL_STOPPED)
		{
			alDeleteSources(1, &it->source);
			ASSERT_AL_ERROR(__FILE__, __LINE__);
			
			stopped.push_back(it.handle());
			
		}
	}
	
	for (auto& h : stopped)
	{
		audioScene.soundSources.destroy(h);
	}
}

void OpenAlSoft::endRender()
{
	
}

SoundSourceHandle OpenAlSoft::play(const AudioSceneHandle& audioSceneHandle, const SoundHandle& soundHandle, const glm::vec3& position)
{
	auto buffer = soundHandles_[soundHandle];
	
	auto handle = audioSceneHandles_[audioSceneHandle].soundSources.create();
	auto& soundSource = audioSceneHandles_[audioSceneHandle].soundSources[handle];
	
	alGenSources(1, &soundSource.source);
	ASSERT_AL_ERROR(__FILE__, __LINE__);
	
	alSourcef(soundSource.source, AL_PITCH, 1);
	alSourcef(soundSource.source, AL_GAIN, 1);
	alSource3f(soundSource.source, AL_POSITION, position.x, position.y, position.z);
	alSource3f(soundSource.source, AL_VELOCITY, 0, 0, 0);
	alSourcei(soundSource.source, AL_LOOPING, AL_FALSE);
	
	ASSERT_AL_ERROR(__FILE__, __LINE__);
	
	soundSource.buffer = buffer;
	
	alSourcei(soundSource.source, AL_BUFFER, soundSource.buffer);
	ASSERT_AL_ERROR(__FILE__, __LINE__);
	
	alSourcePlay(soundSource.source);
    ASSERT_AL_ERROR(__FILE__, __LINE__);
	
	return handle;
}

void OpenAlSoft::stop(const AudioSceneHandle& audioSceneHandle, const SoundSourceHandle& soundSourceHandle)
{
	
}

void OpenAlSoft::stopAll(const AudioSceneHandle& audioSceneHandle)
{
	
}

SoundHandle OpenAlSoft::createSound(const IAudio& audio)
{
    LOG_INFO(logger_, "OpenAL creating sound: length: %s, format: %s, frequency: %s, bitsPerSample: %s, channels: %s", audio.length(), audio.format(), audio.frequency(), audio.bitsPerSample(), static_cast<uint32>(audio.channels()));

	auto handle = soundHandles_.create();
	auto& buffer = soundHandles_[handle];
	
	alGenBuffers(1, &buffer);
	ASSERT_AL_ERROR(__FILE__, __LINE__);

    if (isSupportedFormat(audio.format()))
    {
        const ALenum format = getFormat(audio.format(), audio.frequency(), audio.bitsPerSample(), audio.channels());
        alBufferData(buffer, format, audio.data().data(), audio.length(), audio.frequency());
        ASSERT_AL_ERROR(__FILE__, __LINE__);
    }
    else
    {
        LOG_INFO(logger_, "OpenAL unsupported format '%s', converting audio...", audio.format());

        const Audio convertedAudio = createConvertedAudio(audio);
        const ALenum format = getFormat(convertedAudio.format(), convertedAudio.frequency(), convertedAudio.bitsPerSample(), convertedAudio.channels());

        LOG_INFO(logger_, "OpenAL converted audio: length: %s, format: %s, frequency: %s, bitsPerSample: %s, channels: %s", convertedAudio.length(), convertedAudio.format(), convertedAudio.frequency(), convertedAudio.bitsPerSample(), static_cast<uint32>(convertedAudio.channels()));

        alBufferData(buffer, format, convertedAudio.data().data(), convertedAudio.length(), convertedAudio.frequency());
        ASSERT_AL_ERROR(__FILE__, __LINE__);
    }
	
	return handle;
}

void OpenAlSoft::destroy(const SoundHandle soundHandle)
{
    auto& buffer = soundHandles_[soundHandle];

    alDeleteBuffers(1, &buffer);

    soundHandles_.destroy(soundHandle);
}

ListenerHandle OpenAlSoft::createListener(const AudioSceneHandle& audioSceneHandle, const glm::vec3& position)
{
	return audioSceneHandles_[audioSceneHandle].listenerHandle;
}

void OpenAlSoft::setPosition(const AudioSceneHandle& audioSceneHandle, const SoundSourceHandle& soundSourceHandle, const float32 x, const float32 y, const float32 z)
{
	
}

void OpenAlSoft::setPosition(const AudioSceneHandle& audioSceneHandle, const SoundSourceHandle& soundSourceHandle, const glm::vec3& position)
{
	
}

glm::vec3 OpenAlSoft::position(const AudioSceneHandle& audioSceneHandle, const SoundSourceHandle& soundSourceHandle) const
{
	return glm::vec3();
}

void OpenAlSoft::setPosition(const AudioSceneHandle& audioSceneHandle, const ListenerHandle& listenerHandle, const float32 x, const float32 y, const float32 z)
{
	
}

void OpenAlSoft::setPosition(const AudioSceneHandle& audioSceneHandle, const ListenerHandle& listenerHandle, const glm::vec3& position)
{
	
}

glm::vec3 OpenAlSoft::position(const AudioSceneHandle& audioSceneHandle, const ListenerHandle& listenerHandle) const
{
	return glm::vec3();
}

}
}
}
