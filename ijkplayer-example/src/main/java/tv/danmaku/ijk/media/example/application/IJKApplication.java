package tv.danmaku.ijk.media.example.application;

import android.app.Application;

public class IJKApplication extends Application {


    @Override
    public void onCreate() {
        super.onCreate();



        registerActivityLifecycleCallbacks(new IJKActivityLifecycleCallbacks());
    }



}
