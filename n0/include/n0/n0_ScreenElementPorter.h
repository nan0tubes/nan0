#ifndef __NAN0_SCREENELEMENTPORTER_H__
#define __NAN0_SCREENELEMENTPORTER_H__

#include <json/json.h>

namespace n0
{
	class Json::Value;

	// SCREEN ELEMENT
	class ScreenElementPorter
	{
	public:
		enum EDataType
		{
			DataType_Json = 0,
			DataType_XML,
			DataType_Binary,
		};

	protected:
		ScreenElementPorter() { }

		static ScreenElement * LoadFromJson(const std::string & filename);
		// Recursive parsing function, called by LoadFromJson() to parse the Json hierarchy into ScreenElements
		static ScreenElement * ParseJsonNode(const Json::Value & node);
		static bool SaveToJson(const std::string & filename, ScreenElement * pRootElement);
		// Recursive 'parsing' function, called by SaveToJson() to parse the ScreenElement hierarchy into Json
		static void CreateJsonNode(Json::Value & jVal, ScreenElement * pElement);

		static ScreenElement * LoadFromXML(const std::string & filename);
		static bool SaveToXML(const std::string & filename, ScreenElement * pRootElement);

		static ScreenElement * LoadFromBinary(const std::string & filename);
		static bool SaveToBinary(const std::string & filename, ScreenElement * pRootElement);

		// Basically an element factory, called by the various parsing functions to create the proper version (inherited class) of ScreenElement
		static ScreenElement * CreateElement(const std::string & elementType);

	public:
		virtual ~ScreenElementPorter() { }

		static ScreenElement * Load(const std::string & filename, EDataType dataType)
		{
			if (dataType == DataType_Json)
				return LoadFromJson(filename);
			if (dataType == DataType_XML)
				return LoadFromXML(filename);
			if (dataType == DataType_Binary)
				return LoadFromBinary(filename);
			return NULL;
		}

		static bool Save(const std::string & filename, ScreenElement * pRootElement, EDataType dataType)
		{
			if (dataType == DataType_Json)
				return SaveToJson(filename, pRootElement);
			if (dataType == DataType_XML)
				return SaveToXML(filename, pRootElement);
			if (dataType == DataType_Binary)
				return SaveToBinary(filename, pRootElement);
			return false;
		}
	}; // class ScreenElementPorter
} // namespace n0

#endif // __NAN0_SCREENELEMENTPORTER_H__