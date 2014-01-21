package com.los4fantasticos.contrasticos;

import java.io.OutputStream;
import java.util.UUID;
import android.bluetooth.*;
import android.util.Log;

// Transmite datos por bluetooth
public class BluetoothTransmitter {

	// Constantes
	private final String MAC_ADDRESS = "20:13:11:07:10:20";
	private final String TAG = "Contrastico";
	
	private BluetoothAdapter blueblue;
	private BluetoothDevice  device;
	private BluetoothSocket  socket;
	private OutputStream     outStream;
	
	public BluetoothTransmitter() {
		this.blueblue = BluetoothAdapter.getDefaultAdapter();
	}
	
	public boolean isSupported() {
		return this.blueblue != null;
	}
	
	public boolean enableBluetooth() {
		// Check if the device support Bluetooth
		if (this.blueblue == null)
			return false;
		
		// If it's enabled do nothing
		return this.blueblue.isEnabled();
	}
	
	public void close() {
		try {
			this.outStream.close();
			this.socket.close();
		} catch (Exception e) {
			Log.d(TAG, "Error al cerrar el buffer");
		}
	}
	
	public boolean connectDevice() {
		this.device = this.blueblue.getRemoteDevice(MAC_ADDRESS);
		UUID uuid = this.device.getUuids()[0].getUuid();

		try {
			Log.d(TAG, "Buscando dispositivo");
			this.socket = this.device.createRfcommSocketToServiceRecord(uuid);
		} catch (Exception e) {
			Log.d(TAG, e.getMessage());
			return false;
		}
		
		// Make sure it's not discoverying
		this.blueblue.cancelDiscovery();
		
		// Try to connect
		try {
			Log.d(TAG, "Intentando conectar");
			this.socket.connect();
		} catch (Exception e) {
			Log.d(TAG, e.getMessage());
			return false;
		}
		
		// Try to get the output buffer
		try {
			Log.d(TAG, "Intentando obtener buffer");
			this.outStream = this.socket.getOutputStream();
		} catch(Exception e) {
			Log.d(TAG, e.getMessage());
			return false;
		}
		
		return true;
	}

	public void sendString(String msg) {
		if (this.outStream == null)
			return;
		
		try {
			this.outStream.write(msg.getBytes());
			this.outStream.flush();
		} catch (Exception e) {
			Log.d(TAG, "Imposible enviar datos");
		}
	}
}
