# AndroidStudio_Ncnn_example
android studio下用cmake的方式使用ncnn的例子

新建了一个ncnnshell的库，里面用c++将ncnn的接口封成自己想要的接口，其中会链接ncnn的静态库并生成ncnnshell的静态库
然后native-lib会去调用ncnnshell静态库

ncnn源码的编译：
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI="armeabi-v7a" -DANDROID_ARM_NEON=ON -DCMAKE_BUILD_TYPE=Release     -DANDROID_PLATFORM=android-14 ..

其中ndk使用版本为17
