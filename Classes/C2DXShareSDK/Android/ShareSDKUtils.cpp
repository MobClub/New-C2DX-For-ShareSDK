#include "ShareSDKUtils.h"

#if 1
#define  LOG_TAG    "ShareSDKUtils"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

#ifdef __cplusplus
extern "C" {
#endif

C2DXAuthResultEvent authCb;
C2DXGetUserInfoResultEvent infoCb;
C2DXShareResultEvent shareCb;
C2DXAddFriendResultEvent followFriendCb;
C2DXGetFriendsResultEvent getFriendsCb;


JNIEXPORT void JNICALL Java_cn_sharesdk_ShareSDKUtils_onJavaCallback
  (JNIEnv * env, jclass thiz, jstring resp) {
	CCJSONConverter* json = CCJSONConverter::sharedConverter();
	const char* ccResp = env->GetStringUTFChars(resp, JNI_FALSE);
	CCLog("ccResp = %s", ccResp);
	__Dictionary* dic = json->dictionaryFrom(ccResp);
	env->ReleaseStringUTFChars(resp, ccResp);
	CCNumber* status = (CCNumber*) dic->objectForKey("status"); // Success = 1, Fail = 2, Cancel = 3
	CCNumber* action = (CCNumber*) dic->objectForKey("action"); //  1 = ACTION_AUTHORIZING,  8 = ACTION_USER_INFOR,9 = ACTION_SHARE
	CCNumber* platform = (CCNumber*) dic->objectForKey("platform");
	__Dictionary* res = (__Dictionary*) dic->objectForKey("res");
	CCNumber* reqID = (CCNumber*) dic->objectForKey("reqID");
	// TODO add codes here
	if(1 == status->getIntValue()){
		callBackComplete(reqID->getIntValue(), action->getIntValue(), platform->getIntValue(), res);
	}else if(2 == status->getIntValue()){
		callBackError(reqID->getIntValue(), action->getIntValue(), platform->getIntValue(), res);
	}else{
		callBackCancel(reqID->getIntValue(), action->getIntValue(), platform->getIntValue(), res);
	}
	
	dic->release();
}

void callBackComplete(int reqID, int action, int platformId, __Dictionary* res){
	CCLog("complete callback");
	if (action == 1 && NULL != authCb) { // 1 = ACTION_AUTHORIZING
		authCb(reqID, C2DXResponseStateSuccess, (C2DXPlatType) platformId, NULL);
	} else if (action == 8 && NULL != infoCb) { // 8 = ACTION_USER_INFOR 
		infoCb(reqID, C2DXResponseStateSuccess, (C2DXPlatType) platformId, res);
	} else if (action == 9 && NULL != shareCb) { // 9 = ACTION_SHARE
		shareCb(reqID, C2DXResponseStateSuccess, (C2DXPlatType) platformId, NULL);
	} else if (action == 6 && NULL != followCb) { // 6 = FOLLOW_FRIEND
		followFriendCb(reqID, C2DXResponseStateSuccess, (C2DXPlatType) platformId, res);
	} else if (action == 2 && NULL != getFriendsCb){ // 2 = ACTION_GET_FRIEND_LIST
		getFriendsCb(reqID, C2DXResponseStateSuccess, (C2DXPlatType) platformId, res);
	}
}

void callBackError(int reqID, int action, int platformId, __Dictionary* res){
	if (action == 1 && NULL != authCb) { // 1 = ACTION_AUTHORIZING
		authCb(reqID, C2DXResponseStateFail, (C2DXPlatType) platformId, res);
	} else if (action == 8 && NULL != infoCb) { // 8 = ACTION_USER_INFOR 2 = ACTION_GET_FRIEND_LIST
		infoCb(reqID, C2DXResponseStateFail, (C2DXPlatType) platformId, res);
	} else if (action == 9 && NULL != shareCb) { // 9 = ACTION_SHARE
		shareCb(reqID, C2DXResponseStateFail, (C2DXPlatType) platformId, res);
	} else if (action == 6 && NULL != followCb) { // 6 = FOLLOW_FRIEND
		followFriendCb(reqID, C2DXResponseStateSuccess, (C2DXPlatType) platformId, res);
	} else if (action == 2 && NULL != getFriendsCb){ // 2 = ACTION_GET_FRIEND_LIST
		getFriendsCb(reqID, C2DXResponseStateSuccess, (C2DXPlatType) platformId, res);
	}
}

void callBackCancel(int reqID, int action, int platformId, __Dictionary* res){
	if (action == 1 && NULL != authCb) { // 1 = ACTION_AUTHORIZING
		authCb(reqID, C2DXResponseStateCancel, (C2DXPlatType) platformId, NULL);
	} else if (action == 8 && NULL != infoCb) { // 8 = ACTION_USER_INFOR 2 = ACTION_GET_FRIEND_LIST
		infoCb(reqID, C2DXResponseStateCancel, (C2DXPlatType) platformId, NULL);
	} else if (action == 9 && NULL != shareCb) { // 9 = ACTION_SHARE
		shareCb(reqID, C2DXResponseStateCancel, (C2DXPlatType) platformId, NULL);
	} else if (action == 6 && NULL != followCb) { // 6 = FOLLOW_FRIEND
		followFriendCb(reqID, C2DXResponseStateSuccess, (C2DXPlatType) platformId, NULL);
	} else if (action == 2 && NULL != getFriendsCb){ // 2 = ACTION_GET_FRIEND_LIST
		getFriendsCb(reqID, C2DXResponseStateSuccess, (C2DXPlatType) platformId, NULL);
	}
}

bool getMethod(JniMethodInfo &mi, const char *methodName, const char *paramCode) {
	return JniHelper::getStaticMethodInfo(mi, "cn/sharesdk/ShareSDKUtils", methodName, paramCode);
}

void releaseMethod(JniMethodInfo &mi) {
	mi.env->DeleteLocalRef(mi.classID);
}

bool rigisterAppAndSetPlatformConfig(const char* appKey, __Dictionary *platformInfos) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "initSDKAndSetPlatfromConfig", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (!isHave) {
		return false;
	}
	
	jstring jInfo = NULL;
	if (platformInfos != NULL) {
		CCJSONConverter* json = CCJSONConverter::sharedConverter();
		const char* ccInfo = json->strFrom(info);
		jInfo = mi.env->NewStringUTF(ccInfo);
	}
	
	mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, appKey, jInfo);
	releaseMethod(mi);
	return true;
}

bool authorize(int reqID, int platformId, C2DXAuthResultEvent callback) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "authorize", "(II)V");
	if (!isHave) {
		return false;
	}

	mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, reqID, platformId);
	releaseMethod(mi);
	authCb = callback;
	return true;
}

bool cancelAuthorize(int platformId) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "removeAccount", "(I)V");
	if (!isHave) {
		return false;
	}

	mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platformId);
	releaseMethod(mi);
	return true;
}

bool isAuthorizedValid(int platformId) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "isAuthValid", "(I)Z");
	if (!isHave) {
		return false;
	}

	jboolean valid = mi.env->CallStaticBooleanMethod(mi.classID, mi.methodID, platformId);
	releaseMethod(mi);
	return valid == JNI_TRUE;
}

bool isClientValid(int platformId) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "isClientValid", "(I)Z");
	if (!isHave) {
		return false;
	}

	jboolean valid = mi.env->CallStaticBooleanMethod(mi.classID, mi.methodID, platformId);
	releaseMethod(mi);
	return valid == JNI_TRUE;
}

bool getUserInfo(int reqID, int platformId, C2DXGetUserInfoResultEvent callback){
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "showUser", "(II)V");
	if (!isHave) {
		return false;
	}
	mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, reqID, platformId);
	releaseMethod(mi);
	infoCb = callback;
	return true;
}

bool addFriend(int reqID, int platformId, const char* account, C2DXAddFriendResultEvent callback){
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "followFriend", "(IILjava/lang/String;)V");
	if(!isHave){
		return false;
	}
	jstring jContent = mi.env->NewStringUTF(account);
	mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, reqID, platformId, jContent);
	releaseMethod(mi);
	followCb = callback;

	return true;
}

__Dictionary* getAuthInfo(int platformId){
	JniMethodInfo mi;
	__Dictionary* dic;
	bool isHave = getMethod(mi, "getAuthInfo", "(I)Ljava/lang/String;");
	CCJSONConverter* json = CCJSONConverter::sharedConverter();
	jstring userInfo = (jstring) mi.env->CallStaticObjectMethod(mi.classID, mi.methodID, platformId);
	const char* ccResp = mi.env->GetStringUTFChars(userInfo, JNI_FALSE);
	CCLog("userInfo = %s", ccResp);
	dic = json->dictionaryFrom(ccResp);
	releaseMethod(mi);

	return dic;
}

bool shareContent(int reqID, __Array *platTypes, __Dictionary *content, C2DXShareResultEvent callback){
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "shareContent", "(IILjava/lang/String;)V");
	if (!isHave) {
		return false;
	}

	CCJSONConverter* json = CCJSONConverter::sharedConverter();
	const char* ccContent = json->strFrom(content);
	jstring jContent = mi.env->NewStringUTF(ccContent);
	// free(ccContent);

	mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, reqID, platTypes, jContent);
	releaseMethod(mi);
	shareCb = callback;
	return true;
}

bool getFriendList(int reqID, int platformId, int count, int page, C2DXGetFriendsResultEvent callback){
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "getFriendList", "(IIII)V");
	if (!isHave) {
		return false;
	}
	mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, reqID, platformId, count, page);
	releaseMethod(mi);
	infoCb = callback;
	return true;
}

bool onekeyShare(int reqID, int platformId, __Dictionary *content, C2DXShareResultEvent callback) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "onekeyShare", "(IILjava/lang/String;)V");
	if (!isHave) {
		return false;
	}

	CCJSONConverter* json = CCJSONConverter::sharedConverter();
	const char* ccContent = json->strFrom(content);
	jstring jContent = mi.env->NewStringUTF(ccContent);

	mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, reqID, platformId, jContent);
	releaseMethod(mi);
	
	shareCb = callback;
	return true;
}

void toastShow(const char *msg) {
    JniMethodInfo mi;
    bool isHave = getMethod(mi, "toast", "(Ljava/lang/String;)V");

    jstring jContent = mi.env->NewStringUTF(msg);

    mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, jContent);
    releaseMethod(mi);

    return;
}

#ifdef __cplusplus
}
#endif
