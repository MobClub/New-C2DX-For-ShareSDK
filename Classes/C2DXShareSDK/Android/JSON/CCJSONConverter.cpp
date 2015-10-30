//
//  CCJSONConverter.cpp
//  cocos2d-x-jc
//
//  Created by LIN BOYU on 11/14/12.
//
//

#include "CCJSONConverter.h"

static CCJSONConverter _sharedConverter;

CCJSONConverter * CCJSONConverter::sharedConverter()
{
    static bool firstUse = true;
    if (firstUse)
    {
        firstUse = false;
    }
    return &_sharedConverter;
}

char * CCJSONConverter::strFrom(__Dictionary *Dictionary)
{
    CCAssert(Dictionary, "CCJSONConverter:can not convert a null pointer");
    cJSON * json = cJSON_CreateObject();
    convertDictionaryToJson(Dictionary, json);
    char* returnStr = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return returnStr;
}

__Dictionary * CCJSONConverter::dictionaryFrom(const char *str)
{
    cJSON * json = cJSON_Parse(str);
    if (!json || json->type!=cJSON_Object) {
        if (json) {
            cJSON_Delete(json);
        }
        return NULL;
    }
    CCAssert(json && json->type==cJSON_Object, "CCJSONConverter:wrong json format");
    __Dictionary * Dictionary = new __Dictionary();
    convertJsonToDictionary(json, Dictionary);
    cJSON_Delete(json);
    return Dictionary;
}

void CCJSONConverter::convertJsonToDictionary(cJSON *json, __Dictionary *Dictionary)
{
    Dictionary->removeAllObjects();
    cJSON * j = json->child;
    while (j) {
        Ref * obj = getJsonObj(j);
        Dictionary->setObject(obj, j->string);
        CCLog("Dictionary setObject -- addObject success  %s", j->string);
        j = j->next;
    }
}

void CCJSONConverter::convertDictionaryToJson(__Dictionary *Dictionary, cJSON *json)
{
#if COCOS2D_VERSION >= 0x00030000
    DictElement * pElement = NULL;
#else
    CCDictElement * pElement = NULL;
#endif
    CCDICT_FOREACH(Dictionary, pElement){
        Ref * obj = pElement->getObject();
        cJSON * jsonItem = getObjJson(obj);
        cJSON_AddItemToObject(json, pElement->getStrKey(), jsonItem);
    }
}

void CCJSONConverter::convertJsonToArray(cJSON * json, __Array * array)
{
    array->removeAllObjects();
    int size = cJSON_GetArraySize(json);
    for (int i=0; i<size; i++) {
        cJSON * jsonItem = cJSON_GetArrayItem(json, i);
        Ref * objItem = getJsonObj(jsonItem);
        array->addObject(objItem);
    }
    CCLog("convertJsonToArray -- end");
}

void CCJSONConverter::convertArrayToJson(__Array * array, cJSON * json)
{
    Ref * obj = NULL;
    CCARRAY_FOREACH(array, obj){
        cJSON * jsonItem = getObjJson(obj);
        cJSON_AddItemToArray(json, jsonItem);
    }
}

cJSON * CCJSONConverter::getObjJson(Ref * obj)
{
    std::string s = typeid(*obj).name();
    if(s.find("Dictionary")!=std::string::npos){
        cJSON * json = cJSON_CreateObject();
        convertDictionaryToJson((__Dictionary *)obj, json);
        return json;
    }else if(s.find("Array")!=std::string::npos){
        cJSON * json = cJSON_CreateArray();
        convertArrayToJson((__Array *)obj, json);
        return json;
    }else if(s.find("String")!=std::string::npos){
        __String * s = (__String *)obj;
        cJSON * json = cJSON_CreateString(s->getCString());
        return json;
    }else if(s.find("CCNumber")!=std::string::npos){
        CCNumber * n = (CCNumber *)obj;
        cJSON * json = cJSON_CreateNumber(n->getDoubleValue());
        return json;
    }else if(s.find("CCNull")!=std::string::npos){
        cJSON * json = cJSON_CreateNull();
        return json;
    }
    CCLog("CCJSONConverter encountered an unrecognized type");
    return NULL;
}

Ref * CCJSONConverter::getJsonObj(cJSON * json)
{
    switch (json->type) {
        case cJSON_Object:
        {
        	CCLog("cJSON_Object");
            __Dictionary * Dictionary = new __Dictionary();
            convertJsonToDictionary(json, Dictionary);
            return Dictionary;
        }
        case cJSON_Array:
        {
        	CCLog("cJSON_Array");
            //__Array * array = new __Array();
        	cocos2d::__Array* array;
        	array = __Array::create();
        	array->retain();
            convertJsonToArray(json, array);
            return array;
        }
        case cJSON_String:
        {
        	CCLog("cJSON_String");
            __String * string = new __String(json->valuestring);
            return string;
        }
        case cJSON_Number:
        {
        	CCLog("cJSON_Number");
            CCNumber * number = new CCNumber(json->valuedouble);
            return number;
        }
        case cJSON_True:
        {
        	CCLog("cJSON_True");
            CCNumber * boolean = new CCNumber(1);
            return boolean;
        }
        case cJSON_False:
        {
        	CCLog("cJSON_False");
            CCNumber * boolean = new CCNumber(0);
            return boolean;
        }
        case cJSON_NULL:
        {
        	CCLog("cJSON_NULL");
            CCNull * null = new CCNull();
            return null;
        }
        default:
        {
            CCLog("CCJSONConverter encountered an unrecognized type");
            return NULL;
        }
    }
}
