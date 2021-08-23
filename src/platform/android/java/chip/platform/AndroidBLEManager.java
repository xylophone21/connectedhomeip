package chip.platform;

import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.util.Log;

import java.util.UUID;

import chip.devicecontroller.AndroidChipStack;
import chip.devicecontroller.ChipDeviceController;

public class AndroidBLEManager implements BLEManager {
    @Override
    public int init() {
//        mServiceMode = ConnectivityManager::kCHIPoBLEServiceMode_Enabled;
//        mFlags.ClearAll().Set(Flags::kAdvertisingEnabled, CHIP_DEVICE_CONFIG_CHIPOBLE_ENABLE_ADVERTISING_AUTOSTART && !mIsCentral);
//        mFlags.Set(Flags::kFastAdvertisingEnabled, true);
//
//        memset(mDeviceName, 0, sizeof(mDeviceName));
//
//        OnChipBleConnectReceived = HandleIncomingBleConnection;
//
//        PlatformMgr().ScheduleWork(DriveBLEState, 0);

        return 0;
    }

    @Override
    public long setFlag(long flag, boolean isSet) {
        return 0;
    }

    @Override
    public boolean hasFlag(long flag) {
        return false;
    }

    @Override
    public boolean onSubscribeCharacteristic(int connId, byte[] svcId, byte[] charId) {
        //todo, copy AndroidChipStack->onSubscribeCharacteristic here
        return false;
    }

    @Override
    public boolean onUnsubscribeCharacteristic(int connId, byte[] svcId, byte[] charId) {
        return false;
    }

    @Override
    public boolean onCloseConnection(int connId) {
        return false;
    }

    @Override
    public int onGetMTU(int connId) {
        return 0;
    }

    @Override
    public boolean onSendWriteRequest(int connId, byte[] svcId, byte[] charId, byte[] characteristicData) {
        return false;
    }

    @Override
    public void onNotifyChipConnectionClosed(int connId) {

    }

    @Override
    public void onNewConnection(int discriminator) {

    }
}
