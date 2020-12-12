#ifndef OPENALSOFT_H_
#define OPENALSOFT_H_

#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <AL/al.h>
#include <AL/alc.h>

#include "audio/IAudioEngine.hpp"

#include "al/OpenAl.hpp"

#include "handles/HandleVector.hpp"
#include "utilities/Properties.hpp"
#include "fs/IFileSystem.hpp"
#include "logger/ILogger.hpp"
#include "../src/Audio.hpp"

using namespace ice_engine::audio::openalsoft::al;

namespace ice_engine
{
namespace audio
{
namespace openalsoft
{
/*
struct AudioData
{
	float32 pitch;
	float32 gain;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 direction;
};
*/
struct SoundSource
{
	ALuint source;
	ALuint buffer;
};

struct AudioScene
{
	handles::HandleVector<SoundSource, SoundSourceHandle> soundSources;
	ListenerHandle listenerHandle = ListenerHandle(1);
};

class OpenAlSoft : public IAudioEngine
{
public:
	OpenAlSoft(utilities::Properties* properties, fs::IFileSystem* fileSystem, logger::ILogger* logger);
	~OpenAlSoft() override;
	
	OpenAlSoft(const OpenAlSoft& other) = delete;

	AudioSceneHandle createAudioScene() override;
	void destroyAudioScene(const AudioSceneHandle& audioSceneHandle) override;

    void tick(const AudioSceneHandle audioSceneHandle, const float32 delta) override;
	
	void beginRender() override;
	void render(const AudioSceneHandle& audioSceneHandle) override;
	void endRender() override;
	
	SoundSourceHandle play(const AudioSceneHandle& audioSceneHandle, const SoundHandle& soundHandle, const glm::vec3& position) override;
	
	void stop(const AudioSceneHandle& audioSceneHandle, const SoundSourceHandle& soundSourceHandle) override;
	void stopAll(const AudioSceneHandle& audioSceneHandle) override;
	
	SoundHandle createSound(const IAudio& audio) override;

    void destroy(const SoundHandle soundHandle) override;

    ListenerHandle createListener(const AudioSceneHandle& audioSceneHandle, const glm::vec3& position) override;
	
	void setPosition(const AudioSceneHandle& audioSceneHandle, const SoundSourceHandle& soundSourceHandle, const float32 x, const float32 y, const float32 z) override;
	void setPosition(const AudioSceneHandle& audioSceneHandle, const SoundSourceHandle& soundSourceHandle, const glm::vec3& position) override;
	glm::vec3 position(const AudioSceneHandle& audioSceneHandle, const SoundSourceHandle& soundSourceHandle) const override;
	
	void setPosition(const AudioSceneHandle& audioSceneHandle, const ListenerHandle& listenerHandle, const float32 x, const float32 y, const float32 z) override;
	void setPosition(const AudioSceneHandle& audioSceneHandle, const ListenerHandle& listenerHandle, const glm::vec3& position) override;
	glm::vec3 position(const AudioSceneHandle& audioSceneHandle, const ListenerHandle& listenerHandle) const override;

private:
	ALCdevice* device_ = nullptr;
	ALCcontext* context_ = nullptr;

	utilities::Properties* properties_;
	fs::IFileSystem* fileSystem_;
	logger::ILogger* logger_;
	
	handles::HandleVector<ALuint, SoundHandle> soundHandles_;
	handles::HandleVector<AudioScene, AudioSceneHandle> audioSceneHandles_;
};

}
}
}

#endif /* OPENALSOFT_H_ */
