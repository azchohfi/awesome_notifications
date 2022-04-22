#include "BitmapUtils.h"

#include "StringUtils.h"

#include <regex>

std::wstring BitmapUtils::GetBitmapFromSource(std::string bitmapPath, bool roundedBitmap) {

    std::wstring returnedBitmap;
    switch (GetMediaSourceType(bitmapPath)) {

        case MediaSource::Resource:
            //returnedBitmap = GetBitmapFromResource(bitmapPath);
            break;

        case MediaSource::File:
            //returnedBitmap = GetBitmapFromFile(bitmapPath);
            break;

        case MediaSource::Asset:
            //returnedBitmap = GetBitmapFromAsset(bitmapPath);
            break;

        case MediaSource::Network:
            //returnedBitmap = GetBitmapFromUrl(CleanMediaPath(bitmapPath));
            returnedBitmap = StringUtils::ToWString(CleanMediaPath(bitmapPath));
            break;

        case MediaSource::Unknown:
            break;
    }

    // if(returnedBitmap != null && roundedBitmap){
    //     returnedBitmap = RoundBitmap(returnedBitmap);
    // }

    return returnedBitmap;
}

/*
std::string BitmapUtils::GetBitmapFromResource(std::string bitmapReference){
    int resourceId = getDrawableResourceId(bitmapReference);
    if(resourceId <= 0) return null;
    return BitmapFactory.decodeResource(context.getResources(), resourceId);
}

std::string BitmapUtils::GetBitmapFromAsset(std::string bitmapPath) {
    bitmapPath = MediaUtils.CleanMediaPath(bitmapPath);

    if(bitmapPath == null) return null;

    //std::string appDir = context.getApplicationInfo().dataDir;
    //std::string filePathName = appDir +"/app_flutter/"+ bitmapPath;

    std::string bitmap = null;
    InputStream inputStream = null;
    try {

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            inputStream = context.getAssets().open("flutter_assets/" + bitmapPath);
        } else {
            std::string assetLookupKey = FlutterMain.getLookupKeyForAsset(bitmapPath);
            AssetManager assetManager = context.getAssets();
            AssetFileDescriptor assetFileDescriptor = assetManager.openFd(assetLookupKey);
            inputStream = assetFileDescriptor.createInputStream();
        }

        bitmap = BitmapFactory.decodeStream(inputStream);
        return bitmap;
    } catch (Exception e) {
        e.printStackTrace();
    }
    return null;
}
*/
