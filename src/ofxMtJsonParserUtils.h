//
//  ofxMtJsonParserUtils.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 25/03/15.
//
//

#pragma once

#include "ofxJSON.h"
#include "ofTypes.h"

class ofxMtJsonParserUtils{

public:
	static std::string initFromJsonString(const ofxJSONElement& json, const std::string& key, bool verbose, ofMutex * mutex = NULL);
	static int initFromJsonInt(const ofxJSONElement& json, const std::string& key, bool verbose, ofMutex * mutex = NULL);
	static float initFromJsonFloat(const ofxJSONElement& json, const std::string& key, bool verbose, ofMutex * mutex = NULL);
	static bool initFromJsonBool(const ofxJSONElement& json, const std::string& key, bool verbose, ofMutex * mutex = NULL);
};
