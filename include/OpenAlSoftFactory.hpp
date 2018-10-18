#ifndef OPENALSOFTFACTORY_H_
#define OPENALSOFTFACTORY_H_

#include <memory>

#include "audio/IAudioEngine.hpp"
#include "audio/IAudioEngineFactory.hpp"

namespace ice_engine
{
namespace audio
{
namespace openalsoft
{

class OpenAlSoftFactory : public IAudioEngineFactory
{
public:
	OpenAlSoftFactory();
	virtual ~OpenAlSoftFactory();

	virtual std::unique_ptr<IAudioEngine> create(
		utilities::Properties* properties,
		fs::IFileSystem* fileSystem,
		logger::ILogger* logger
	) override;

};

}
}
}

#endif /* OPENALSOFTFACTORY_H_ */
