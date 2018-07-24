#ifndef CORE_CONTEXTINFO_H
#define CORE_CONTEXTINFO_H

namespace LiteRenderer
{
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
}

#endif // !CORE_CONTEXTINFO_H

