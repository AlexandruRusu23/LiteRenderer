#ifndef CONTEXTINFO_H
#define CONTEXTINFO_H

namespace Core
{
	struct ContextInfo
	{
		int majorVersion;
		int minorVersion;
		bool useCoreProfile;

		ContextInfo() = delete;

		ContextInfo(int majorVersion, int minorVersion, bool useCoreProfile)
		{
			this->majorVersion = majorVersion;
			this->minorVersion = minorVersion;
			this->useCoreProfile = useCoreProfile;
		}

		ContextInfo(const ContextInfo& contextInfo)
		{
			majorVersion = contextInfo.majorVersion;
			minorVersion = contextInfo.minorVersion;
			useCoreProfile = contextInfo.useCoreProfile;
		}

		void operator=(const ContextInfo& contextInfo)
		{
			majorVersion = contextInfo.majorVersion;
			minorVersion = contextInfo.minorVersion;
			useCoreProfile = contextInfo.useCoreProfile;
		}
	};
}

#endif
