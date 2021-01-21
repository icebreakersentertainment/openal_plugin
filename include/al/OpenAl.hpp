#ifndef OPENAL_H_
#define OPENAL_H_

#include <string>
#include <stdexcept>

#include <boost/optional.hpp>

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

struct AlError
{
    ALenum code = AL_NO_ERROR;
    std::string codeString = "AL_NO_ERROR";
    std::string message = "";
};

inline boost::optional<AlError> getAlError()
{
    const ALenum error = alGetError();

    if (error != AL_NO_ERROR)
    {
        AlError e;
        e.code = error;

        switch (error)
        {
            case AL_INVALID_NAME:		e.codeString = "AL_INVALID_NAME";	    break;
            case AL_INVALID_ENUM:	    e.codeString = "AL_INVALID_ENUM";	    break;
            case AL_INVALID_VALUE:      e.codeString = "AL_INVALID_VALUE";	    break;
            case AL_INVALID_OPERATION:  e.codeString = "AL_INVALID_OPERATION";  break;
            case AL_OUT_OF_MEMORY:      e.codeString = "AL_OUT_OF_MEMORY";	    break;

            default:                    e.codeString = "Unknown Error";	        break;
        }

        const auto message = alGetString(error);

        if (message != nullptr) e.message = message;

        return e;
    }

    return boost::none;
}

inline void checkAlError(const std::string& filename, const int line)
{
    const auto e = getAlError();

    if (e)
    {
        throw std::runtime_error(filename + " (" + std::to_string(line) + "): " + e->codeString + ": " + e->message);
    }
}

inline void checkAlError()
{
    const auto e = getAlError();

    if (e)
	{
		throw std::runtime_error(e->codeString + ": " + e->message);
	}
}

}
}
}
}

#endif /* OPENAL_H_ */
