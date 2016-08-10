//
//  ofxMtJsonParser.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 24/03/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxSimpleHttp.h"
#include "ofxJSON.h"
#include "ofxMtJsonParserConfig.h"

#include "ofxMtJsonParserThread.h"


//Parser, Object
template <class P,class O>
class ofxMtJsonParser: public ofThread{

public:

	ofxMtJsonParser();

	void downloadAndParse(string jsonURL_,
						  string jsonDownloadDir_,
						  int numThreads,
						  ofxMtJsonParserConfig* args);

	void update();

	// STATUS //
	bool isBusy();
	bool isDownloadingJson(){ return state == DOWNLOADING_JSON; }
	bool isCheckingJson(){ return state == CHECKING_JSON; }
	bool isParsingJson(){ return state == PARSING_JSON_IN_SUBTHREADS; }
	vector<float> getPerThreadProgress(); //returns a vector of size NumThreads with a float with [0..1]
	float getTotalProgress();
	string getDrawableState();

	int getNumEntriesInJson(){return numEntriesInJson;}

	// EVENTS //

	ofEvent<ofxSimpleHttpResponse> eventJsonDownloaded;
	ofEvent<ofxSimpleHttpResponse> eventJsonDownloadFailed;
	ofEvent<bool> eventJsonInitialCheckOK;
	ofEvent<bool> eventJsonParseFailed;
	ofEvent<vector<O*> > eventAllObjectsParsed;


	vector<O*> getParsedObjects(); //use only after you got the "eventDontentReady" callback

	ofxSimpleHttp & getHttp(){return http;} //in case you want to config it

protected:

	enum State{
		IDLE = 0,
		DOWNLOADING_JSON,
		DOWNLOAD_FAILED,
		CHECKING_JSON,
		JSON_PARSE_FAILED,
		PARSING_JSON_IN_SUBTHREADS,
		MERGE_THREAD_RESULTS,
		FINISHED
	};

	ofxSimpleHttp http;
	State state;

	string jsonURL;
	string jsonDownloadDir;
	string jsonAbsolutePath;
	ofxJSONElement * json;

	int numEntriesInJson;

	ofxMtJsonParserConfig *args;

	ofMutex printMutex;

	int numThreads;
	vector<ofxMtJsonParserThread<O>*> threads;
	vector<ofxMtJsonParserThreadConfig> threadConfigs;

	void setState(State s);

	void updateParsing();
	void startParsingInSubThreads();
	void checkLocalJsonAndSplitWorkload();
	void mergeThreadResults();

	void onJsonDownload(ofxSimpleHttpResponse & arg);

	void threadedFunction();

	vector<O*> parsedObjects;
};

#include "ofxMtJsonParser.inl"
