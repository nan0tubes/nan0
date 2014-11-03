#include "n0/n0.h"

namespace n0
{
	ScreenElement * ScreenElementPorter::CreateElement(const std::string & elementType)
	{
		if (elementType.compare("ScreenElement") == 0)
			return new ScreenElement();
		//TODO: add additional types

		return NULL;
	}

	ScreenElement * ScreenElementPorter::ParseJsonNode(const Json::Value& node)
	{
		std::string type = node["type"].asString();
		ScreenElement * pElement = CreateElement(type);
		if (pElement)
		{
			pElement->SetName(node["name"].asString());
			pElement->SetVisible(node["visibility"].asBool());
			pElement->SetBackgroundColour(strtoul(node["bgcolour"].asCString(), NULL, 16));
			pElement->SetAnchor(node["anchor"].asUInt());
			pElement->SetPosition(node["position"][0].asInt(), node["position"][1].asInt());
			pElement->SetSize(node["size"][0].asInt(), node["size"][1].asInt());

			//TODO: add some type specific properties

			for (u32 i = 0; i < node["children"].size(); ++i)
			{
				pElement->AddChild(ParseJsonNode(node["children"][i]));
			}
		}

		return pElement;
	}

	void ScreenElementPorter::CreateJsonNode(Json::Value & jVal, ScreenElement * pElement)
	{
		jVal["type"] = pElement->GetType();
		jVal["name"] = pElement->GetName();
		jVal["visibility"] = pElement->IsVisible();
		jVal["bgcolour"] = pElement->GetBackgroundColour().GetHex();
		jVal["anchor"] = pElement->GetAnchor();
		jVal["position"][0] = pElement->GetPosition().x;
		jVal["position"][1] = pElement->GetPosition().y;
		jVal["size"][0] = pElement->GetSize().x;
		jVal["size"][1] = pElement->GetSize().y;

		std::vector<ScreenElement*> * pChildren = pElement->GetChildren();
		u32 i = 0;
		if (pChildren->size())
		{
			for (std::vector<ScreenElement*>::const_iterator it = pChildren->begin(); it != pChildren->end(); ++it, ++i)
			{
				CreateJsonNode(jVal["children"][i], *it);
			}
		}
		else
		{
			jVal["children"][0];
		}
	}

	ScreenElement * ScreenElementPorter::LoadFromJson(const std::string & filename)
	{
		Json::Value jRoot;
		Json::Reader jReader;
		std::ifstream fileContent(filename, std::ifstream::binary);
		bool wasParsed = jReader.parse(fileContent, jRoot, false);
		if (wasParsed)
		{
			return ParseJsonNode(jRoot);
		}

		return NULL;
	}

	bool ScreenElementPorter::SaveToJson(const std::string & filename, ScreenElement * pRootElement)
	{
		std::ofstream out(filename, std::ofstream::out);
		Json::Value jsonRootNode;
		CreateJsonNode(jsonRootNode, pRootElement);
		out << jsonRootNode;
		return false;
	}

	ScreenElement * ScreenElementPorter::LoadFromXML(const std::string & filename)
	{
		return NULL;
	}

	bool ScreenElementPorter::SaveToXML(const std::string & filename, ScreenElement * pRootElement)
	{
		return false;
	}

	ScreenElement * ScreenElementPorter::LoadFromBinary(const std::string & filename)
	{
		return NULL;
	}

	bool ScreenElementPorter::SaveToBinary(const std::string & filename, ScreenElement * pRootElement)
	{
		return false;
	}
}