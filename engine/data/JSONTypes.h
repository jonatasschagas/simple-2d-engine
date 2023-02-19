#pragma once
#ifndef JSONTYPES_H
#define JSONTYPES_H

#include <rapidjson/document.h>

using namespace rapidjson;

typedef rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator > > > JSONObject;
typedef rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator > > > ConstJSONObject;

#endif //JSONTYPES_H
