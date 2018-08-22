package uner.ii.ncnndemo3;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private static final int SELECT_IMAGE = 1;

    private TextView textview;
    private ImageView imageView;
    private Bitmap yourSelectedImage = null;
    String initRet = null;
    String debugInitRet = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        byte[] param = null;
        byte[] bin = null;
        try{
            InputStream param_ = getAssets().open("selfMobileSSD.param.bin");
            int available = param_.available();
            param = new byte[available];
            int byteCode = param_.read(param);
            param_.close();
        }
        catch (IOException e)
        {
            Log.e("MainActivity", "file error");
        }
        try{
            InputStream bin_ = getAssets().open("selfMobileSSD.bin");
            int available = bin_.available();
            bin = new byte[available];
            int byteCode = bin_.read(bin);
            bin_.close();
        }
        catch (IOException e)
        {
            Log.e("MainActivity", "file error");
        }

        initRet = Init(param,bin);
        debugInitRet = debugInit(param,bin);

        textview = (TextView) findViewById(R.id.textview);
        imageView = (ImageView) findViewById(R.id.imageView);

        Button buttonDebug = (Button) findViewById(R.id.buttonDebug);
        buttonDebug.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View arg0) {
                textview.setText(debugInitRet);
            }
        });

        Button buttonImage = (Button) findViewById(R.id.buttonImage);
        buttonImage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View arg0) {
                Intent i = new Intent(Intent.ACTION_PICK);
                i.setType("image/*");
                startActivityForResult(i, SELECT_IMAGE);
            }
        });

        Button buttonDetect = (Button) findViewById(R.id.buttonDetect);
        buttonDetect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View arg0) {
                if (yourSelectedImage == null)
                    return;

                //textview.setText(initRet+" "+ncnnShell.DetectSSD(300,300,yourSelectedImage));
                textview.setText(DetectSSD(300,300,yourSelectedImage));

            }
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == RESULT_OK && null != data) {
            Uri selectedImage = data.getData();

            try
            {
                if (requestCode == SELECT_IMAGE) {
                    Bitmap bitmap = decodeUri(selectedImage);

                    Bitmap rgba = bitmap.copy(Bitmap.Config.ARGB_8888, true);

                    // resize to 227x227
                    yourSelectedImage = Bitmap.createScaledBitmap(rgba, 300, 300, false);

                    imageView.setImageBitmap(yourSelectedImage);
                }
            }
            catch (FileNotFoundException e)
            {
                Log.e("MainActivity", "FileNotFoundException");
                return;
            }
        }
    }


    private Bitmap decodeUri(Uri selectedImage) throws FileNotFoundException
    {
        // Decode image size
        BitmapFactory.Options o = new BitmapFactory.Options();
        o.inJustDecodeBounds = true;
        BitmapFactory.decodeStream(getContentResolver().openInputStream(selectedImage), null, o);

        // The new size we want to scale to
        final int REQUIRED_SIZE = 400;

        // Find the correct scale value. It should be the power of 2.
        int width_tmp = o.outWidth, height_tmp = o.outHeight;
        int scale = 1;
        while (true) {
            if (width_tmp / 2 < REQUIRED_SIZE
                    || height_tmp / 2 < REQUIRED_SIZE) {
                break;
            }
            width_tmp /= 2;
            height_tmp /= 2;
            scale *= 2;
        }

        // Decode with inSampleSize
        BitmapFactory.Options o2 = new BitmapFactory.Options();
        o2.inSampleSize = scale;
        return BitmapFactory.decodeStream(getContentResolver().openInputStream(selectedImage), null, o2);
    }



    public native String stringFromJNI();
    public native String debugInit(byte[] param, byte[] bin);
    public native String Init(byte[] param, byte[] bin);
    public static native String DetectSSD(int h, int w, Bitmap bitmap);
}
