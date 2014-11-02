#include "fwInternal.h"

GameConfig::GameConfig() :
	 m_DeviceDriverType(irr::video::EDT_OPENGL)
	,m_WindowDimensions(irr::core::dimension2d<irr::u32>(720, 1280))
	,m_BitDepth(16)
	,m_IsFullscreen(false)
	,m_UseStencilBuffer(false)
	,m_UseVSync(false)
	,m_Framerate(60)
	,m_HasUnsavedData(false)
{
	strncpy(m_BlackboxConfigFilename, "config/blackboxconfig.xml", kMaxFilenameLength);
}

GameConfig::~GameConfig()
{
}

bool GameConfig::Load()
{
	const char configFile[kStrLen_Huge] = "config/config.xml";
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError error = doc.LoadFile(configFile);

	// if file load was successful
	if (error == tinyxml2::XML_SUCCESS)
	{
		// irrlicht config
		tinyxml2::XMLElement * configElement = doc.FirstChildElement("Irrlicht");
		if (configElement)
		{
			const tinyxml2::XMLAttribute * attribute = configElement->FirstAttribute();
			while (attribute)
			{
				const u32 stringHash = Hash(attribute->Name());

				if (stringHash == Hash("deviceDriver"))
					m_DeviceDriverType = (irr::video::E_DRIVER_TYPE)attribute->UnsignedValue();
				else if (stringHash == Hash("windowHeight"))
					m_WindowDimensions.Height = attribute->UnsignedValue();
				else if (stringHash == Hash("windowWidth"))
					m_WindowDimensions.Width = attribute->UnsignedValue();
				else if (stringHash == Hash("bitDepth"))
					m_BitDepth = attribute->UnsignedValue();
				else if (stringHash == Hash("isFullscreen"))
					m_IsFullscreen = attribute->BoolValue();
				else if (stringHash == Hash("useStencilBuffer"))
					m_UseStencilBuffer = attribute->BoolValue();
				else if (stringHash == Hash("useVSync"))
					m_UseVSync = attribute->BoolValue();
				else if (stringHash == Hash("framerate"))
					m_Framerate = attribute->UnsignedValue();

				attribute = attribute->Next();
			}
		}

		// blackbox config filename
		tinyxml2::XMLElement * blackBoxElement = doc.FirstChildElement("BlackBox");
		if (blackBoxElement)
		{
			const tinyxml2::XMLAttribute * attribute = blackBoxElement->FirstAttribute();
			while (attribute)
			{
				const u32 stringHash = Hash(attribute->Name());

				if (stringHash == Hash("configFile"))
					strncpy(m_BlackboxConfigFilename, attribute->Value(), kMaxFilenameLength);

				attribute = attribute->Next();
			}
		}
	}
	// file not found (or some other error); create new default config file
	else
	{
		Save();
	}

	return true;
}

bool GameConfig::Save()
{
	const char filename[kMaxFilenameLength] = "config/config.xml";
	tinyxml2::XMLDocument doc;

	// Irrlicht Node
	tinyxml2::XMLElement* irrlichtElement = doc.NewElement("Irrlicht");
	if (irrlichtElement)
	{
		irrlichtElement->SetAttribute("deviceDriver", m_DeviceDriverType);
		irrlichtElement->SetAttribute("windowHeight", m_WindowDimensions.Height);
		irrlichtElement->SetAttribute("windowWidth", m_WindowDimensions.Width);
		irrlichtElement->SetAttribute("bitDepth", m_BitDepth);
		irrlichtElement->SetAttribute("isFullscreen", m_IsFullscreen);
		irrlichtElement->SetAttribute("useStencilBuffer", m_UseStencilBuffer);
		irrlichtElement->SetAttribute("useVSync", m_UseVSync);
		irrlichtElement->SetAttribute("framerate", m_Framerate);
	}

	// blackbox config filename
	tinyxml2::XMLElement* blackboxElement = doc.NewElement("BlackBox");
	if (blackboxElement)
		blackboxElement->SetAttribute("configFile", m_BlackboxConfigFilename);

	doc.SaveFile(filename);

	m_HasUnsavedData = false;
	return true;
}

// SETTERS
//======================================================================
void GameConfig::SetDeviceDriverType(const irr::video::E_DRIVER_TYPE & type)
{
	m_DeviceDriverType = type;
	m_HasUnsavedData = true;
}

void GameConfig::SetWindowDimensions(const irr::core::dimension2d<irr::u32> & dims)
{
	m_WindowDimensions = dims;
	m_HasUnsavedData = true;
}

void GameConfig::SetBitDepth(const irr::u32 & bitDepth)
{
	m_BitDepth = bitDepth;
	m_HasUnsavedData = true;
}

void GameConfig::SetIsFullscreen(const bool & isFullscreen)
{
	m_IsFullscreen = isFullscreen;
	m_HasUnsavedData = true;
}

void GameConfig::SetUseStencilBuffer(const bool & useStencilBuffer)
{
	m_UseStencilBuffer = useStencilBuffer;
	m_HasUnsavedData = true;
}

void GameConfig::SetUseVSync(const bool & useVSync)
{
	m_UseVSync = useVSync;
	m_HasUnsavedData = true;
}

void GameConfig::SetFramerate(const irr::u32 & duration)
{
	m_Framerate = duration;
	m_HasUnsavedData = true;
}
