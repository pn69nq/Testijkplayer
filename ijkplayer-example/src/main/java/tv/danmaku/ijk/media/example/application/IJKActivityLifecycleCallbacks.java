package tv.danmaku.ijk.media.example.application;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.util.Log;
import android.view.View;


/**
 * <pre>
 *     author : chenzengqiang
 *     e-mail : chenzengqiang@hongdoujiao.com
 *     time   : 2018/03/28
 *     desc   :
 *     version: 1.0
 * </pre>
 */
public class IJKActivityLifecycleCallbacks implements Application.ActivityLifecycleCallbacks {

    private final String TAG = IJKActivityLifecycleCallbacks.class.getSimpleName();

    @Override
    public void onActivityCreated(Activity activity, Bundle savedInstanceState) {
        Log.e(TAG, "onFragmentCreated "+activity.getClass().toString());
    }

    @Override
    public void onActivityStarted(Activity activity) {
        if(activity instanceof FragmentActivity){
            ((FragmentActivity)activity).getSupportFragmentManager().registerFragmentLifecycleCallbacks(new FragmentManager.FragmentLifecycleCallbacks(){
                @Override
                public void onFragmentPreAttached(FragmentManager fm, Fragment f, Context context) {
                    super.onFragmentPreAttached(fm, f, context);
                }

                @Override
                public void onFragmentAttached(FragmentManager fm, Fragment f, Context context) {
                    super.onFragmentAttached(fm, f, context);
                }

                @Override
                public void onFragmentCreated(FragmentManager fm, Fragment f, Bundle savedInstanceState) {
                    super.onFragmentCreated(fm, f, savedInstanceState);
                    Log.e(TAG, "onFragmentCreated "+f.getClass().toString());
                }

                @Override
                public void onFragmentActivityCreated(FragmentManager fm, Fragment f, Bundle savedInstanceState) {
                    super.onFragmentActivityCreated(fm, f, savedInstanceState);
                    Log.e(TAG,"onFragmentActivityCreated "+f.getClass().toString());
                }

                @Override
                public void onFragmentViewCreated(FragmentManager fm, Fragment f, View v, Bundle savedInstanceState) {
                    super.onFragmentViewCreated(fm, f, v, savedInstanceState);
                }

                @Override
                public void onFragmentStarted(FragmentManager fm, Fragment f) {
                    super.onFragmentStarted(fm, f);
                }

                @Override
                public void onFragmentResumed(FragmentManager fm, Fragment f) {
                    super.onFragmentResumed(fm, f);
//                    FunCom.showLog(0,TAG,  f.toString()+"==="+f.getClass().toString());
                }

                @Override
                public void onFragmentPaused(FragmentManager fm, Fragment f) {
                    super.onFragmentPaused(fm, f);
                }

                @Override
                public void onFragmentStopped(FragmentManager fm, Fragment f) {
                    super.onFragmentStopped(fm, f);
                }

                @Override
                public void onFragmentSaveInstanceState(FragmentManager fm, Fragment f, Bundle outState) {
                    super.onFragmentSaveInstanceState(fm, f, outState);
                }

                @Override
                public void onFragmentViewDestroyed(FragmentManager fm, Fragment f) {
                    super.onFragmentViewDestroyed(fm, f);
                    Log.e(TAG, "onFragmentViewDestroyed "+f.getClass().toString());
                }

                @Override
                public void onFragmentDestroyed(FragmentManager fm, Fragment f) {
                    super.onFragmentDestroyed(fm, f);
                    Log.e(TAG, "onFragmentDestroyed "+f.getClass().toString());
                }

                @Override
                public void onFragmentDetached(FragmentManager fm, Fragment f) {
                    super.onFragmentDetached(fm, f);
                }
            },true);

        }
    }

    @Override
    public void onActivityResumed(Activity activity) {

    }

    @Override
    public void onActivityPaused(Activity activity) {

    }

    @Override
    public void onActivityStopped(Activity activity) {

    }

    @Override
    public void onActivitySaveInstanceState(Activity activity, Bundle outState) {

    }

    @Override
    public void onActivityDestroyed(Activity activity) {

    }
}
