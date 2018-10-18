#ifndef OPENALSOFTPLUGIN_H_
#define OPENALSOFTPLUGIN_H_

#include <memory>

#include "IAudioPlugin.hpp"

namespace ice_engine
{

class OpenAlSoftPlugin : public IAudioPlugin
{
public:
	OpenAlSoftPlugin();
	virtual ~OpenAlSoftPlugin();

	virtual std::string getName() const override;

	virtual std::unique_ptr<audio::IAudioEngineFactory> createFactory() const override;

};

}

#endif /* OPENALSOFTPLUGIN_H_ */
