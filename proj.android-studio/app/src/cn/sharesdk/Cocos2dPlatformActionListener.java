package cn.sharesdk;

import java.util.HashMap;

import com.mob.tools.utils.Hashon;
import com.mob.tools.utils.UIHandler;

import android.os.Message;
import android.os.Handler.Callback;

import cn.sharesdk.framework.Platform;
import cn.sharesdk.framework.PlatformActionListener;
import cn.sharesdk.framework.ShareSDK;

public class Cocos2dPlatformActionListener implements PlatformActionListener {

	private int reqID;
	private Callback c2dCallback;
	
	public Cocos2dPlatformActionListener(int reqID, Callback callback) {
		this.reqID = reqID;
		this.c2dCallback = callback;
	}	
	
	public void onComplete(Platform platform, int action, HashMap<String, Object> res) {
		if (ShareSDKUtils.DEBUG) {
			System.out.println("onComplete");
			System.out.println(res == null ? "" : res.toString());
		}
		HashMap<String, Object> map = new HashMap<String, Object>();
		map.put("platform", ShareSDK.platformNameToId(platform.getName()));
		map.put("action", action);
		map.put("status", 1); // Success = 1, Fail = 2, Cancel = 3
		if(action == 8 || action == 2){
			//action = 2, 8, 获取用户列表与用户信息才放入   
			map.put("res", res);
		}
		map.put("reqID", reqID);
		Message msg = new Message();
		msg.obj = new Hashon().fromHashMap(map);
		UIHandler.sendMessage(msg, c2dCallback);
	}

	public void onError(Platform platform, int action, Throwable t) {
		if (ShareSDKUtils.DEBUG) {
			System.out.println("onError");
			t.printStackTrace();
		}
		HashMap<String, Object> map = new HashMap<String, Object>();
		map.put("platform", ShareSDK.platformNameToId(platform.getName()));
		map.put("action", action);
		map.put("status", 2); // Success = 1, Fail = 2, Cancel = 3
		map.put("res", throwableToMap(t));
		map.put("reqID", reqID);
		Message msg = new Message();
		msg.obj = new Hashon().fromHashMap(map);
		UIHandler.sendMessage(msg, c2dCallback);
	}

	public void onCancel(Platform platform, int action) {
		if (ShareSDKUtils.DEBUG) {
			System.out.println("onCancel");
		}
		HashMap<String, Object> map = new HashMap<String, Object>();
		map.put("platform", ShareSDK.platformNameToId(platform.getName()));
		map.put("action", action);
		map.put("status", 3); // Success = 1, Fail = 2, Cancel = 3
		map.put("reqID", reqID);
		Message msg = new Message();
		msg.obj = new Hashon().fromHashMap(map);
		UIHandler.sendMessage(msg, c2dCallback);
	}	

	private static HashMap<String, Object> throwableToMap(Throwable t) {
		HashMap<String, Object> map = new HashMap<String, Object>();
		map.put("msg", t.getMessage());
		Throwable cause = t.getCause();
		if (cause != null) {
			map.put("cause", throwableToMap(cause));
		}
		return map;
	}
}
