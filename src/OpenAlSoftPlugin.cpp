#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT

#include "OpenAlSoftPlugin.hpp"

#include "OpenAlSoftFactory.hpp"

namespace ice_engine
{

OpenAlSoftPlugin::OpenAlSoftPlugin()
{
}

OpenAlSoftPlugin::~OpenAlSoftPlugin()
{
}

std::string OpenAlSoftPlugin::getName() const
{
	return std::string("openalsoft");
}

std::unique_ptr<audio::IAudioEngineFactory> OpenAlSoftPlugin::createFactory() const
{
	std::unique_ptr<audio::IAudioEngineFactory> ptr = std::make_unique< audio::openalsoft::OpenAlSoftFactory >();
	
	return std::move( ptr );
}

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT OpenAlSoftPlugin plugin;
OpenAlSoftPlugin plugin;

}
