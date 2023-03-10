echo "Downloading NDK"

mkdir ndk
cd ndk
if [[ ! -d "r17c" ]]; then
	wget https://dl.google.com/android/repository/android-ndk-r17c-linux-x86_64.zip
	unzip android-ndk-r17c-linux-x86_64.zip
	mv android-ndk-r17c r17c
	rm android-ndk-r17c-linux-x86_64.zip
fi

cd ..

echo "Downloading libraries"
if [[ ! -f "libs.zip" ]]; then
	wget https://files.dogotrigger.xyz/libs.zip
	unzip libs.zip
fi

rm build -rf

mkdir build
cd build
mkdir x86
mkdir armeabi-v7a

export NDK="$PWD/../ndk/r17c"

cmake .. -DCMAKE_ANDROID_NDK=$NDK -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DANDROID=1 -G "Unix Makefiles"
make all -j 12
cp ../out_a/libgdmod.so armeabi-v7a/
rm ../out_a Make* cmake* CMake* -rf
