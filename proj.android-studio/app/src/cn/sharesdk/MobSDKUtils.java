package cn.sharesdk;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.plugin.PluginWrapper;

import android.content.Context;
import android.text.TextUtils;

import com.mob.MobSDK;
import com.mob.OperationCallback;
import com.mob.PrivacyPolicy;
import com.mob.commons.dialog.entity.MobPolicyUi;
import com.mob.tools.utils.ResHelper;

public class MobSDKUtils {
    private static Context context;

    static {
    	context = Cocos2dxActivity.getContext().getApplicationContext();
    }

    private MobSDKUtils() {

	}

    /**
     * 获取MobSDK隐私协议内容
     *
     * @param url true返回MobTech隐私协议链接，其它返回协议的内容
     * @return
     */
    public static String getPrivacyPolicy(boolean url) {
        PrivacyPolicy policy;
        if (url) {
            policy = MobSDK.getPrivacyPolicy(MobSDK.POLICY_TYPE_URL);
        } else {
            policy = MobSDK.getPrivacyPolicy(MobSDK.POLICY_TYPE_TXT);
        }
        return policy.getContent();
    }

    /**
     * 提交用户授权结果给MobSDK
     *
     * @param granted true表示用户已授权，false表示用户未授权
     */
    public static void submitPolicyGrantResult(boolean granted) {
        MobSDK.submitPolicyGrantResult(granted, new OperationCallback<Void>() {
            public void onComplete(Void data) {
            
            }

            public void onFailure(Throwable t) {
            
            }
        });
    }

    /**
     * 是否允许展示二次确认框
     * <p>
     * 在以下情况下，**个别**接口会**默认**向用户展示隐私协议二次确认框：
     * - 开发者未反馈用户隐私协议授权结果
     * - 用户拒绝隐私协议
     *
     * @param allowDialog true允许，false禁止
     */
    public static void setAllowDialog(boolean allowDialog) {
        MobSDK.setAllowDialog(allowDialog);
    }

    /**
     * 设置二次确认框样式
     *
     * @param backgroundColorId  弹框背景色资源ID
     * @param positiveBtnColorId 同意按钮背景色资源ID
     * @param negativeBtnColorId 拒绝按钮背景色资源ID
     */
    public static void setPolicyUi(int backgroundColorId, int positiveBtnColorId, int negativeBtnColorId) {
        MobPolicyUi.Builder builder = new MobPolicyUi.Builder();
        if (backgroundColorId > 0) {
            builder = builder.setBackgroundColorId(backgroundColorId);
        }
        if (positiveBtnColorId > 0) {
            builder = builder.setPositiveBtnColorId(positiveBtnColorId);
        }
        if (negativeBtnColorId > 0) {
            builder = builder.setNegativeBtnColorId(negativeBtnColorId);
        }
        MobSDK.setPolicyUi(builder.build());
    }

    /**
     * 设置二次确认框样式
     *
     * @param backgroundColorRes  弹框背景色资源名
     * @param positiveBtnColorRes 同意按钮背景色资源名
     * @param negativeBtnColorRes 拒绝按钮背景色资源名
     */
    public static void setPolicyUiRes(String backgroundColorRes, String positiveBtnColorRes, String negativeBtnColorRes) {
        int backgroundColorId = ResHelper.getColorRes(context, backgroundColorRes);
        int positiveBtnColorId = ResHelper.getColorRes(context, positiveBtnColorRes);
        int negativeBtnColorId = ResHelper.getColorRes(context, negativeBtnColorRes);
        setPolicyUi(backgroundColorId, positiveBtnColorId, negativeBtnColorId);
    }
}
