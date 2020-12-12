#ifndef OPENAL_H_
#define OPENAL_H_

#include <string>
#include <stdexcept>

#include <AL/al.h>

namespace ice_engine
{
namespace audio
{
namespace openalsoft
{
namespace al
{

#define ASSERT_AL_ERROR(filename, line) checkAlError(filename, line);

inline void checkAlError(const std::string& filename, const int line)
{
	const ALenum error = alGetError();
	const auto errorString = alGetString(error);

	if (error != AL_NO_ERROR)
	{
		throw std::runtime_error(filename + " (" + std::to_string(line) + "): " + std::to_string(error) + ": " + errorString);
	}
}

inline void checkAlError()
{
    const ALenum error = alGetError();
    const auto errorString = alGetString(error);

	if (error != AL_NO_ERROR)
	{
		throw std::runtime_error(std::to_string(error) + ": " + errorString);
	}
}

}
}
}
}

#endif /* OPENAL_H_ */
