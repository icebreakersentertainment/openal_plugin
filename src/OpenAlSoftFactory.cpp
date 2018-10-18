#include "OpenAlSoftFactory.hpp"

#include "OpenAlSoft.hpp"

namespace ice_engine
{
namespace audio
{
namespace openalsoft
{

OpenAlSoftFactory::OpenAlSoftFactory()
{
}

OpenAlSoftFactory::~OpenAlSoftFactory()
{
}

std::unique_ptr<IAudioEngine> OpenAlSoftFactory::create(
	utilities::Properties* properties,
	fs::IFileSystem* fileSystem,
	logger::ILogger* logger
)
{
	std::unique_ptr<IAudioEngine> ptr = std::make_unique< OpenAlSoft >( properties, fileSystem, logger );
	
	return std::move( ptr );
}

}
}
}
