package com.tcl.chip.chiptvserver;

import android.graphics.Bitmap;
import android.graphics.Color;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.util.HashSet;

import chip.appserver.ChipAppServer;
import chip.platform.AndroidBleManager;
import chip.platform.AndroidChipPlatform;
import chip.platform.ChipMdnsCallbackImpl;
import chip.platform.NsdManagerServiceResolver;
import chip.platform.PreferencesConfigurationManager;
import chip.platform.PreferencesKeyValueStoreManager;
import chip.setuppayload.DiscoveryCapability;
import chip.setuppayload.SetupPayload;
import chip.setuppayload.SetupPayloadParser;

public class MainActivity extends AppCompatActivity {

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

        //TODO: Get these parameters from PreferencesConfigurationManager
        HashSet<DiscoveryCapability> discoveryCapabilities = new HashSet<>();
        discoveryCapabilities.add(DiscoveryCapability.ON_NETWORK);
        SetupPayload payload = new SetupPayload(
                0
                , 9050
                , 65279
                , 0
                , discoveryCapabilities
                , 3840
                , 20202021);

        SetupPayloadParser parser = new SetupPayloadParser();
        try {
            String qrCode = parser.getQrCodeFromPayload(payload);
            mQrCodeTxt.setText(qrCode);

            Bitmap qrCodeBitmap = QRUtils.createQRCodeBitmap(qrCode, 800, 800);
            mQrCode.setImageBitmap(qrCodeBitmap);
        } catch (SetupPayloadParser.SetupPayloadException e) {
            e.printStackTrace();
        }

        try {
            String manualPairingCode = parser.getManualEntryCodeFromPayload(payload);
            mManualPairingCodeTxt.setText("ManualPairingCode:" + manualPairingCode);
        } catch (SetupPayloadParser.SetupPayloadException e) {
            e.printStackTrace();
        }

        chipAppServer.startApp();
    }
}