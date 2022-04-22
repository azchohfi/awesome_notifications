#pragma once

#include <string>

#include "../notifications/enums/MediaSource.h"
#include "MediaUtils.h"

class BitmapUtils : public MediaUtils {
 public:
    static std::wstring GetBitmapFromSource(std::string bitmapPath, bool roundedBitmap);
    /*

    static int GetResId(std::string variableName, Class<?> c) {

        try {
            Field idField = c.getDeclaredField(variableName);
            return idField.getInt(idField);
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    static int GetDrawableResourceId(std::string bitmapReference){
        bitmapReference = MediaUtils.cleanMediaPath(bitmapReference);
        std::string[] reference = bitmapReference.split("\\/");
        try {
            int resId;

            std::string type = reference[0];
            std::string label = reference[1];

            // Resources protected from obfuscation
            // https://developer.android.com/studio/build/shrink-code#strict-reference-checks
            std::string name = std::string.format("res_%1s", label);
            resId = context.getResources().getIdentifier(name, type, context.getPackageName());

            if(resId == 0){
                resId = context.getResources().getIdentifier(label, type, context.getPackageName());
            }

            return resId;

        } catch (Exception e) {
            e.printStackTrace();
        }

        return 0;
    }

    static Bitmap RoundBitmap(Bitmap bitmap) {
        Bitmap output = Bitmap.createBitmap(bitmap.getWidth(),
                bitmap.getHeight(), Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(output);

        final int color = 0xff424242;
        final Paint paint = new Paint();
        final Rect rect = new Rect(0, 0, bitmap.getWidth(), bitmap.getHeight());

        paint.setAntiAlias(true);
        canvas.drawARGB(0, 0, 0, 0);
        paint.setColor(color);
        // canvas.drawRoundRect(rectF, roundPx, roundPx, paint);
        canvas.drawCircle(bitmap.getWidth() / 2, bitmap.getHeight() / 2,
                bitmap.getWidth() / 2, paint);
        paint.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.SRC_IN));
        canvas.drawBitmap(bitmap, rect, rect, paint);
        //Bitmap _bmp = Bitmap.createScaledBitmap(output, 60, 60, false);
        //return _bmp;
        return output;
    }
    */
/*
    static std::string GetBitmapFromResource(std::string bitmapReference);

    static std::string GetBitmapFromAsset(std::string bitmapPath);
    */
/*
    static bool IsValidBitmap(std::string mediaPath) {

        if (mediaPath != null) {

            if (MediaUtils.matchMediaType(MEDIA_VALID_NETWORK, mediaPath, false)) {
                return true;
            }

            if (MediaUtils.matchMediaType(MEDIA_VALID_FILE, mediaPath)) {
                // TODO MISSING IMPLEMENTATION
                return true;
            }

            if (MediaUtils.matchMediaType(MEDIA_VALID_RESOURCE, mediaPath)) {
                return isValidDrawableResource(mediaPath);
            }

            if (MediaUtils.matchMediaType(MEDIA_VALID_ASSET, mediaPath)) {
                return true;
            }

        }
        return false;
    }
    */

 private:

/*
    static Bitmap GetBitmapFromFile(std::string bitmapPath){
        bitmapPath = MediaUtils.CleanMediaPath(bitmapPath);
        Bitmap bitmap = null;

        try {
            File imageFile = new File(bitmapPath);
            bitmap = BitmapFactory.decodeFile(imageFile.getAbsolutePath());
        } catch (Exception e) {
            e.printStackTrace();
        }

        return bitmap;
    }

    static Bitmap GetBitmapFromUrl(std::string bitmapUri) {
        bitmapUri = MediaUtils.CleanMediaPath(bitmapUri);
        Bitmap bitmap = null;
        InputStream inputStream = null;
        BufferedInputStream bufferedInputStream = null;

        if(StringUtils.isNullOrEmpty(bitmapUri))
            return null;

        try {
            URLConnection conn = new URL(bitmapUri).openConnection();
            conn.connect();
            inputStream = conn.getInputStream();
            bufferedInputStream = new BufferedInputStream(inputStream, 8192);
            bitmap = BitmapFactory.decodeStream(bufferedInputStream);
        }
        catch (Exception e){
            e.printStackTrace();
        }
        finally {
            if (bufferedInputStream != null)
            {
                try
                {
                    bufferedInputStream.close();
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }
            }
            if (inputStream != null)
            {
                try
                {
                    inputStream.close();
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }
            }
        }

        return bitmap;
    }

    static bool IsValidDrawableResource(std::string name) {
        if(name != null){
            int resourceId = getDrawableResourceId(name);
            return resourceId > 0;
        }
        return false;
    }
    */
};
