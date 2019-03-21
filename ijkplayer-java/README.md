#### 播放器类

组成:
1   播放器代理类(定义播放接口)状态机
    >>>数据源抽象(输入)
    >>>>>>解码
    >>>>>>>>>播放器渲染View类,音频播放(输出)


```
    tv.danmaku.ijk.media.player.IMediaPlayer
    >>>>tv.danmaku.ijk.media.player.MediaPlayerProxy
    >>>>>>>>>tv.danmaku.ijk.media.player.TextureMediaPlayer
    
    >>>>tv.danmaku.ijk.media.player.AbstractMediaPlayer


```


#### 源码阅读

```
    tv.danmaku.ijk.media.player.IjkMediaPlayer.loadLibrariesOnce()
    --->java 层     
            //调用
            public static void loadLibrariesOnce(IjkLibLoader libLoader) {
                synchronized (IjkMediaPlayer.class) {
                    if (!mIsLibLoaded) {
                        if (libLoader == null){
                            libLoader = sLocalLibLoader;
                        }
        
                        //加载so,实际调用System.loadLibrary(libName);
                        libLoader.loadLibrary("ijkffmpeg");
                        libLoader.loadLibrary("ijksdl");
                        libLoader.loadLibrary("ijkplayer");
                        mIsLibLoaded = true;
                    }
                }
            }
    
    ---->native 层
    JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
    {
        JNIEnv* env = NULL;
    
        g_jvm = vm;
        if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
            return -1;
        }
        assert(env != NULL);
    
        //线程同步初始化
        pthread_mutex_init(&g_clazz.mutex, NULL );
    
        // FindClass returns LocalReference ,返回看
        IJK_FIND_JAVA_CLASS(env, g_clazz.clazz, JNI_CLASS_IJKPLAYER);
        //动态注册jni调用的方法
        (*env)->RegisterNatives(env, g_clazz.clazz, g_methods, NELEM(g_methods) );
        //
        ijkmp_global_init();
        ijkmp_global_set_inject_callback(inject_callback);
    
        //ffmpeg 初始化
        FFmpegApi_global_init(env);
    
        return JNI_VERSION_1_4;
    }
    
    JNIEXPORT void JNI_OnUnload(JavaVM *jvm, void *reserved)
    {
        ijkmp_global_uninit();
    
        pthread_mutex_destroy(&g_clazz.mutex);
    }
    
    
    
    
-------------------------------------------------------------------------------------
    
    tv.danmaku.ijk.media.player.IjkMediaPlayer.native_profileBegin("libijkplayer.so")
    ---->java 层
              //public static native void native_profileBegin(String libName);
              
    
    ---->c++层
    Libijkplayer/jni/ijkmedia/ijkplayer/android/ijkplayer_jni.c
        //jni实际调用到部分代码
        static void IjkMediaPlayer_native_profileBegin(JNIEnv *env, jclass clazz, jstring libName)
        {
            MPTRACE("%s\n", __func__);
        
            const char *c_lib_name = NULL;
            static int s_monstartup = 0;
        
            if (!libName)
                return;
        
            if (s_monstartup) {
                ALOGW("monstartup already called\b");
                return;
            }
        
            c_lib_name = (*env)->GetStringUTFChars(env, libName, NULL );
            JNI_CHECK_GOTO(c_lib_name, env, "java/lang/OutOfMemoryError", "mpjni: monstartup: libName.string oom", LABEL_RETURN);
        
            s_monstartup = 1;
            monstartup(c_lib_name);
            ALOGD("monstartup: %s\n", c_lib_name);
        
        LABEL_RETURN:
            if (c_lib_name)
                (*env)->ReleaseStringUTFChars(env, libName, c_lib_name);
        }
    
    
    
-------------------------------------------------------------------------------------  
    
    
    
    
    
    //初始化IjkVideoView
    ----->java 层
            private void initVideoView(Context context) {
                mAppContext = context.getApplicationContext();
                mSettings = new Settings(mAppContext);
        
                initBackground();//初始化 是否允许后台播放
                initRenders();
            }
            ----->调用
                private void initBackground() {
                    .....
                    if (mEnableBackgroundPlay) {
                        MediaPlayerService.intentToStart(getContext());
                        mMediaPlayer = MediaPlayerService.getMediaPlayer();
                        if (mHudViewHolder != null)
                            mHudViewHolder.setMediaPlayer(mMediaPlayer);
                    }
                }
                
-------------------------------------------------------------------------------------      
    
    //设置各种回调
    tv.danmaku.ijk.media.example.widget.media.IjkVideoView.setMediaController()
    
    
    //设置url
    tv.danmaku.ijk.media.example.widget.media.IjkVideoView.setVideoPath()
    
    ---->最终调用到
        private void setVideoURI(Uri uri, Map<String, String> headers) {
            mUri = uri;
            mHeaders = headers;
            mSeekWhenPrepared = 0;
            openVideo();//重要代码(创建播放器)
            requestLayout();
            invalidate();
        }
    -------->openVideo()    
            private void openVideo() {
                if (mUri == null || mSurfaceHolder == null) {
                    // not ready for playback just yet, will try again later
                    return;
                }
                // we shouldn't clear the target state, because somebody might have
                // called start() previously
                release(false);
        
                AudioManager am = (AudioManager) mAppContext.getSystemService(Context.AUDIO_SERVICE);
                am.requestAudioFocus(null, AudioManager.STREAM_MUSIC, AudioManager.AUDIOFOCUS_GAIN);
        
                try {
                    mMediaPlayer = createPlayer(mSettings.getPlayer());
        
                    // TODO: create SubtitleController in MediaPlayer, but we need
                    // a context for the subtitle renderers
                    final Context context = getContext();
                    // REMOVED: SubtitleController
        
                    // REMOVED: mAudioSession
                    mMediaPlayer.setOnPreparedListener(mPreparedListener);
                    mMediaPlayer.setOnVideoSizeChangedListener(mSizeChangedListener);
                    mMediaPlayer.setOnCompletionListener(mCompletionListener);
                    mMediaPlayer.setOnErrorListener(mErrorListener);
                    mMediaPlayer.setOnInfoListener(mInfoListener);
                    mMediaPlayer.setOnBufferingUpdateListener(mBufferingUpdateListener);
                    mMediaPlayer.setOnSeekCompleteListener(mSeekCompleteListener);
                    mMediaPlayer.setOnTimedTextListener(mOnTimedTextListener);
                    mCurrentBufferPercentage = 0;
                    String scheme = mUri.getScheme();
                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M &&
                            mSettings.getUsingMediaDataSource() &&
                            (TextUtils.isEmpty(scheme) || scheme.equalsIgnoreCase("file"))) {
                        IMediaDataSource dataSource = new FileMediaDataSource(new File(mUri.toString()));
                        mMediaPlayer.setDataSource(dataSource);
                    }  else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH) {
                        mMediaPlayer.setDataSource(mAppContext, mUri, mHeaders);
                    } else {
                        mMediaPlayer.setDataSource(mUri.toString());
                    }
                    bindSurfaceHolder(mMediaPlayer, mSurfaceHolder);
                    mMediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
                    mMediaPlayer.setScreenOnWhilePlaying(true);
                    mPrepareStartTime = System.currentTimeMillis();
                    mMediaPlayer.prepareAsync();
                    if (mHudViewHolder != null)
                        mHudViewHolder.setMediaPlayer(mMediaPlayer);
        
                    // REMOVED: mPendingSubtitleTracks
        
                    // we don't set the target state here either, but preserve the
                    // target state that was there before.
                    mCurrentState = STATE_PREPARING;
                    attachMediaController();
                } catch (IOException ex) {
                    Log.w(TAG, "Unable to open content: " + mUri, ex);
                    mCurrentState = STATE_ERROR;
                    mTargetState = STATE_ERROR;
                    mErrorListener.onError(mMediaPlayer, MediaPlayer.MEDIA_ERROR_UNKNOWN, 0);
                } catch (IllegalArgumentException ex) {
                    Log.w(TAG, "Unable to open content: " + mUri, ex);
                    mCurrentState = STATE_ERROR;
                    mTargetState = STATE_ERROR;
                    mErrorListener.onError(mMediaPlayer, MediaPlayer.MEDIA_ERROR_UNKNOWN, 0);
                } finally {
                    // REMOVED: mPendingSubtitleTracks.clear();
                }
            }
            
            
            //核心代码创建播放器
            public IMediaPlayer createPlayer(int playerType) {
                    IMediaPlayer mediaPlayer = null;
            
                    switch (playerType) {
                        //硬编码
                        case Settings.PV_PLAYER__IjkExoMediaPlayer: {
                            IjkExoMediaPlayer IjkExoMediaPlayer = new IjkExoMediaPlayer(mAppContext);
                            mediaPlayer = IjkExoMediaPlayer;
                        }
                        break;
                        case Settings.PV_PLAYER__AndroidMediaPlayer: {
                            AndroidMediaPlayer androidMediaPlayer = new AndroidMediaPlayer();
                            mediaPlayer = androidMediaPlayer;
                        }
                        break;
                        case Settings.PV_PLAYER__IjkMediaPlayer:
                        default: {
                            IjkMediaPlayer ijkMediaPlayer = null;
                            if (mUri != null) {
                                //创建播放器,重要的事情不多说
                                ijkMediaPlayer = new IjkMediaPlayer();
                                ijkMediaPlayer.native_setLogLevel(IjkMediaPlayer.IJK_LOG_DEBUG);
            
                                if (mSettings.getUsingMediaCodec()) {
                                    ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "mediacodec", 1);
                                    if (mSettings.getUsingMediaCodecAutoRotate()) {
                                        ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "mediacodec-auto-rotate", 1);
                                    } else {
                                        ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "mediacodec-auto-rotate", 0);
                                    }
                                    if (mSettings.getMediaCodecHandleResolutionChange()) {
                                        ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "mediacodec-handle-resolution-change", 1);
                                    } else {
                                        ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "mediacodec-handle-resolution-change", 0);
                                    }
                                } else {
                                    ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "mediacodec", 0);
                                }
            
                                if (mSettings.getUsingOpenSLES()) {
                                    ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "opensles", 1);
                                } else {
                                    ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "opensles", 0);
                                }
            
                                String pixelFormat = mSettings.getPixelFormat();
                                if (TextUtils.isEmpty(pixelFormat)) {
                                    ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "overlay-format", IjkMediaPlayer.SDL_FCC_RV32);
                                } else {
                                    ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "overlay-format", pixelFormat);
                                }
                                ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "framedrop", 1);
                                ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "start-on-prepared", 0);
            
                                ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_FORMAT, "http-detect-range-support", 0);
            
                                ijkMediaPlayer.setOption(IjkMediaPlayer.OPT_CATEGORY_CODEC, "skip_loop_filter", 48);
                            }
                            mediaPlayer = ijkMediaPlayer;
                        }
                        break;
                    }
            
                    if (mSettings.getEnableDetachedSurfaceTextureView()) {
                        mediaPlayer = new TextureMediaPlayer(mediaPlayer);
                    }
            
                    return mediaPlayer;
                }
                
                //核心代码创建播放器(实际调用到的代码)
                private void initPlayer(IjkLibLoader libLoader) {
                        loadLibrariesOnce(libLoader);
                        initNativeOnce();
                
                        Looper looper;
                        if ((looper = Looper.myLooper()) != null) {
                            mEventHandler = new EventHandler(this, looper);
                        } else if ((looper = Looper.getMainLooper()) != null) {
                            mEventHandler = new EventHandler(this, looper);
                        } else {
                            mEventHandler = null;
                        }
                
                        /*
                         * Native setup requires a weak reference to our object. It's easier to
                         * create it here than in C++.
                         */
                        native_setup(new WeakReference<IjkMediaPlayer>(this));
                    }
    
    //native 核心代码摘出来
    tv.danmaku.ijk.media.player.IjkMediaPlayer.loadLibrariesOnce()
    tv.danmaku.ijk.media.player.IjkMediaPlayer.initNativeOnce()
    最终调用到---->tv.danmaku.ijk.media.player.IjkMediaPlayer.native_init()
    
    --------->jni 层
    
    tv.danmaku.ijk.media.player.IjkMediaPlayer.native_setup()
    
    
    //
    tv.danmaku.ijk.media.example.widget.media.IjkVideoView.start()
    
         if (isInPlaybackState()) {
            mMediaPlayer.start();//重要代码
            mCurrentState = STATE_PLAYING;
         }
         mTargetState = STATE_PLAYING;
    
        //
    
        

```

