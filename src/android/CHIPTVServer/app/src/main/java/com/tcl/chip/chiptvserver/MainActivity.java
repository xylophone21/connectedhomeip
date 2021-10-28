package com.tcl.chip.chiptvserver;

import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.util.Random;

import chip.appserver.ChipAppServer;
import chip.platform.AndroidBleManager;
import chip.platform.AndroidChipPlatform;
import chip.platform.ChipMdnsCallbackImpl;
import chip.platform.NsdManagerServiceResolver;
import chip.platform.PreferencesConfigurationManager;
import chip.platform.PreferencesKeyValueStoreManager;


public class MainActivity extends AppCompatActivity{
    private ImageView mQrCode;
    private TextView mQrCodeTxt;
    private TextView mManualPairingCodeTxt;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mQrCode = findViewById(R.id.qrCode);
        mQrCodeTxt = findViewById(R.id.qrcode_txt);
        mManualPairingCodeTxt = findViewById(R.id.manualPairingCode_txt);
        ChipAppServer chipAppServer = new ChipAppServer();
        AndroidChipPlatform chipPlatform = new AndroidChipPlatform(new AndroidBleManager(),
                new PreferencesKeyValueStoreManager(this),
                new PreferencesConfigurationManager(this),
                new NsdManagerServiceResolver(this),
                new ChipMdnsCallbackImpl());

//        //  chipAppServer.setSetUpPinCode(getPinCode());
//        chipAppServer.setSetUpPinCode(20202021);
//        mQrCodeTxt.setText("SerialNumber:"+ chipAppServer.getSerialNumber() +
//                ",VendorId:"+ chipAppServer.getVendorId() +
//                ",ProductId:"+ chipAppServer.getProductId() +
//                ",ProductRevision:"+ chipAppServer.getProductRevision() +
//                ",SetUpPinCode:"+ chipAppServer.getSetUpPinCode() +
//                ",Discriminator:"+ chipAppServer.getDiscriminator()+
//                ",DeviceType:"+ chipAppServer.getDeviceType());
//      //  chipAppServer.setConfigurationManager(chipAppServer);
//        chipAppServer.setQRCodeListener(this);
        int i = chipAppServer.startApp();
        Log.d("MainActivity","i = " + i);
        //TODO: set Configuration and getQRCode function will be impletement in setuppayload
    }

    private int getPinCode() {

        Random random = new Random();
        int result = 0;
        for (int i = 0; i < 8; i++) {
            result += (random.nextInt(10) * Math.pow(10, i));
        }
        return result;
    }
}