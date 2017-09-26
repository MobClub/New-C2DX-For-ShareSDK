package cn.sharesdk;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.plugin.PluginWrapper;

import android.content.Context;
import android.os.Handler.Callback;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;
import cn.sharesdk.framework.Platform;
import cn.sharesdk.framework.Platform.ShareParams;
import cn.sharesdk.framework.PlatformDb;
import cn.sharesdk.framework.ShareSDK;
import cn.sharesdk.onekeyshare.OnekeyShare;

import com.mob.MobSDK;
import com.mob.tools.utils.Hashon;
import com.mob.tools.utils.UIHandler;

public class ShareSDKUtils {
	public static boolean DEBUG = true;
	private static boolean disableSSO = true; 
	
	private static Context context;
	private static Hashon hashon;
	private static Callback cb;
	
	private ShareSDKUtils() {

	}

	public static void prepare() {
		context = Cocos2dxActivity.getContext().getApplicationContext();
		hashon = new Hashon();
		cb = new Callback() {
			public boolean handleMessage(final Message msg) {
				PluginWrapper.runOnGLThread(new Runnable() {
					public void run() {
						onJavaCallback((String) msg.obj);
					}
				});
				return false;
			}
		};		
	}

	private static native void onJavaCallback(String resp);

	public static void initSDKAndSetPlatfromConfig(final String appKey,final String appSecret,final String configs) {
		if (DEBUG) {
			System.out.println("initSDKAndSetPlatfromConfig");
		}

		UIHandler.sendEmptyMessage(1, new Callback() {
			public boolean handleMessage(Message msg) {	
				if (!TextUtils.isEmpty(appKey) && !TextUtils.isEmpty(appSecret)) {
					MobSDK.init(context,appKey,appSecret);
				} else if(!TextUtils.isEmpty(appKey)){
					MobSDK.init(context,appKey);
				} else {
					MobSDK.init(context);
				}				
				return true;
			}
		});
		
		UIHandler.sendEmptyMessageDelayed(1, 500, new Callback() {
			@SuppressWarnings("unchecked")
			public boolean handleMessage(Message msg) {					
				Hashon hashon = new Hashon();
				HashMap<String, Object> devInfo = hashon.fromJson(configs);
				ShareSDK.getPlatformList();
				for(Entry<String, Object> entry: devInfo.entrySet()){
					String p = ShareSDK.platformIdToName(Integer.parseInt(entry.getKey()));
					ShareSDK.setPlatformDevInfo(p, (HashMap<String, Object>)entry.getValue());
				}		
				return true;
			}
		});
	}
	
	public static void authorize(int reqID, int platformId) {
		if (DEBUG) {
			System.out.println("authorize");
		}
		String name = ShareSDK.platformIdToName(platformId);
		if(TextUtils.isEmpty(name)){
			ShareSDK.getPlatform(null);
			name = ShareSDK.platformIdToName(platformId);
		}
		Platform plat = ShareSDK.getPlatform(name);
		Cocos2dPlatformActionListener paListaner = new Cocos2dPlatformActionListener(reqID, cb);
		plat.setPlatformActionListener(paListaner);
		plat.SSOSetting(disableSSO);
		plat.authorize();
	}

	public static void removeAccount(int platformId) {
		if (DEBUG) {
			System.out.println("removeAccount");
		}
		String name = ShareSDK.platformIdToName(platformId);
		Platform plat = ShareSDK.getPlatform( name);
		plat.removeAccount(true);
	}

	public static boolean isAuthValid(int platformId) {
		if (DEBUG) {
			System.out.println("isValid");
		}
		String name = ShareSDK.platformIdToName(platformId);
		Platform plat = ShareSDK.getPlatform(name);
		return plat.isAuthValid();
	}
	
	public static boolean isClientValid(int platformId) {
		if (DEBUG) {
			System.out.println("isValid");
		}
		String name = ShareSDK.platformIdToName(platformId);
		Platform plat = ShareSDK.getPlatform( name);
		return plat.isClientValid();
	}	
	
	public static void showUser(int reqID, int platformId) {
		if (DEBUG) {
			System.out.println("showUser");
		}
		String name = ShareSDK.platformIdToName(platformId);
		Platform plat = ShareSDK.getPlatform(name);
		Cocos2dPlatformActionListener paListaner = new Cocos2dPlatformActionListener(reqID, cb);
		plat.setPlatformActionListener(paListaner);
		plat.SSOSetting(disableSSO);
		plat.showUser(null);
	}
	
	public static String getAuthInfo(int platformId){
		if (DEBUG) {
			System.out.println("getAuthInfo");
		}
		
		String name = ShareSDK.platformIdToName(platformId);
		Platform plat = ShareSDK.getPlatform(name);
		HashMap<String, Object> map = new HashMap<String, Object>();
		if(plat.isAuthValid()){
			PlatformDb db = plat.getDb();
			map.put("expiresIn", db.getExpiresIn());
			map.put("expiresTime", db.getExpiresTime());
			map.put("token", db.getToken());
			map.put("tokenSecret", db.getTokenSecret());
			map.put("userGender", db.getUserGender());
			map.put("userID", db.getUserId());
			map.put("openID", db.get("openid"));
			map.put("unionID", db.get("unionid"));
			map.put("userName", db.getUserName());
			map.put("userIcon", db.getUserIcon());
		}
		return hashon.fromHashMap(map);
	}
	
	public static void getFriendList(int reqID, int platformId, int count, int page){
		if (DEBUG) {
			System.out.println("listFriend");
			System.out.println("count:" + count + " page:" + page );
		}
		String name = ShareSDK.platformIdToName(platformId);
		Platform plat = ShareSDK.getPlatform(name);
		Cocos2dPlatformActionListener paListaner = new Cocos2dPlatformActionListener(reqID, cb);
		plat.setPlatformActionListener(paListaner);
		plat.SSOSetting(disableSSO);
		plat.listFriend(count, page, null);
	}
	
	public static void followFriend(int reqID, int platformId, String account){
		if (DEBUG) {
			System.out.println("followFriend");
		}
		String name = ShareSDK.platformIdToName(platformId);
		Platform plat = ShareSDK.getPlatform(name);
		Cocos2dPlatformActionListener paListaner = new Cocos2dPlatformActionListener(reqID, cb);
		plat.setPlatformActionListener(paListaner);
		plat.SSOSetting(disableSSO);
		plat.followFriend(account);
	}

	public static void shareContent(int reqID, int platformId, String contentJson) {
		if (DEBUG) {
			System.out.println("share");
		}
		String name = ShareSDK.platformIdToName(platformId);
		Platform plat = ShareSDK.getPlatform(name);
		Cocos2dPlatformActionListener paListaner = new Cocos2dPlatformActionListener(reqID, cb);
		plat.setPlatformActionListener(paListaner);
		try {
			HashMap<String, Object> content = hashon.fromJson(contentJson);
			content = nativeMapToJavaMap(content);
			ShareParams sp = new ShareParams(content);
			plat.SSOSetting(disableSSO);
			plat.share(sp);
		} catch (Throwable t) {
			paListaner.onError(plat, Platform.ACTION_SHARE, t);
		}
	}
	
	public static void disableSSOWhenAuthorize(boolean disable){
		System.out.println("disableSSOWhenAuthorize:" + disable);
		disableSSO = disable;
	}

	public static void onekeyShare(int reqID, int platformId, String contentJson) {
		if (DEBUG) {
			System.out.println("OnekeyShare" + contentJson);
		}
		
		HashMap<String, Object> content = hashon.fromJson(contentJson);
		HashMap<String, Object> map = nativeMapToJavaMap(content);
		Cocos2dPlatformActionListener paListaner = new Cocos2dPlatformActionListener(reqID, cb);
		
		OnekeyShare oks = new OnekeyShare();
		if (map.containsKey("text")) {
			oks.setText(String.valueOf(map.get("text")));
		}
		if (map.containsKey("imagePath")) {
			oks.setImagePath(String.valueOf(map.get("imagePath")));
		}
		if (map.containsKey("imageUrl")) {
			oks.setImageUrl(String.valueOf(map.get("imageUrl")));
		}
		if (content.containsKey("imageArray")) {
			@SuppressWarnings("unchecked")
			ArrayList<String> imageList = (ArrayList<String>)content.get("imageArray");
			String[] str = (String[])imageList.toArray(new String[imageList.size()]);
			oks.setImageArray(str);
		}
		if (map.containsKey("title")) {
			oks.setTitle(String.valueOf(map.get("title")));
		}
		if (map.containsKey("comment")) {
			oks.setComment(String.valueOf(map.get("comment")));
		}
		if (map.containsKey("url")) {
			oks.setUrl(String.valueOf(map.get("url")));
		}
		if (map.containsKey("titleUrl")) {
			oks.setTitleUrl(String.valueOf(map.get("titleUrl")));
		}
		if (map.containsKey("site")) {
			oks.setSite(String.valueOf(map.get("site")));
		}
		if (map.containsKey("siteUrl")) {
			oks.setSiteUrl(String.valueOf(map.get("siteUrl")));
		}
		if (platformId > 0) {
			oks.setPlatform(ShareSDK.platformIdToName(platformId));
		}
		if(disableSSO) {
			oks.disableSSOWhenAuthorize();
		}
		oks.setCallback(paListaner);

		oks.show(context);
	}

	public static void toast(final String message) {
		Log.e(ShareSDKUtils.class.getName(), message);
		UIHandler.sendEmptyMessage(1, new Callback() {
			@Override
			public boolean handleMessage(Message msg) {
				Toast.makeText(context, message, Toast.LENGTH_LONG).show();
				return true;
			}
		});
	}	

	private static HashMap<String, Object> nativeMapToJavaMap(
			HashMap<String, Object> content) {
		HashMap<String, Object> map = new HashMap<String, Object>();
		
		if (content.get("content") != null) {
			map.put("text", content.get("content"));
		} else if (content.get("text") != null) {
			map.put("text", content.get("text"));
		}
		if (content.get("image") != null) {
			String image = (String) content.get("image");
			if (image != null && image.startsWith("/")) {
				map.put("imagePath", image);
			} else if (!TextUtils.isEmpty(image)) {
				map.put("imageUrl", image);
			}
		}
		if (content.containsKey("imageArray")) {
			map.put("imageArray", content.get("imageArray"));
		}
		if (content.get("title") != null) {
			map.put("title", content.get("title"));
		}
		if (content.get("description") != null) {
			map.put("comment", content.get("description"));
		}
		if (content.get("url") != null) {
			map.put("url", content.get("url"));
		}
		if (content.get("titleUrl") != null) {
			map.put("titleUrl", content.get("titleUrl"));
		}
		if (content.get("site") != null) {
			map.put("site", content.get("site"));
		}
		if (content.get("siteUrl") != null) {
			map.put("siteUrl", content.get("siteUrl"));
		}
		if (content.get("musicUrl") != null) {
			map.put("musicUrl", content.get("musicUrl"));
		}
		if (content.get("extInfo") != null) {
			map.put("extInfo", content.get("extInfo"));
		}
		if (content.get("type") != null) {
			String type = (String) content.get("type");
			int shareType = Integer.parseInt(type);
			if (shareType == 0) {
				shareType = 1;//ios的auto类型，修改成1的text类型
			}
			map.put("shareType", shareType);
		}
		return map;
	}

}
