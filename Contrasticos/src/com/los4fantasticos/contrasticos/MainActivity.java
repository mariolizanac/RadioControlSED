/*
 * Aplicación para controlar coche radiocontrol
 * 
 * Autores: Los 4 fántasticos + Link
 */
package com.los4fantasticos.contrasticos;

import android.os.Bundle;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View.OnClickListener;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;
import android.util.Log;

public class MainActivity extends Activity {

	private final String TAG = "Contrastico";
	
	private Button btnW;
	private Button btnA;
	private Button btnD;
	private Button btnS;
	private RadioButton radioBtnControl;
	private RadioButton radioBtnLuz;
	private RadioButton radioBtnLinea;
	private Button btnConnect;
	private Button btnActivate;
	private Button btnClose;
	private TextView lblStatus;

	private BluetoothTransmitter bt;

	OnTouchListener btnWClick = new OnTouchListener() {
	    @Override
	    public boolean onTouch(View v, MotionEvent event) {
	        if(event.getAction() == MotionEvent.ACTION_DOWN) {
	            bt.sendString("w");
	            return true;
	        } else if (event.getAction() == MotionEvent.ACTION_UP) {
	            bt.sendString("p");
	            return true;
	        }
	        
	        return false;
	    }
	};
	
	OnTouchListener btnSClick = new OnTouchListener() {
	    @Override
	    public boolean onTouch(View v, MotionEvent event) {
	        if(event.getAction() == MotionEvent.ACTION_DOWN) {
	            bt.sendString("s");
	            return true;
	        } else if (event.getAction() == MotionEvent.ACTION_UP) {
	            bt.sendString("p");
	            return true;
	        }
	        
	        return false;
	    }
	};
	
	OnTouchListener btnAClick = new OnTouchListener() {
	    @Override
	    public boolean onTouch(View v, MotionEvent event) {
	        if(event.getAction() == MotionEvent.ACTION_DOWN) {
	            bt.sendString("a");
	            return true;
	        } else if (event.getAction() == MotionEvent.ACTION_UP) {
	            bt.sendString("p");
	            return true;
	        }
	        
	        return false;
	    }
	};
	
	OnTouchListener btnDClick = new OnTouchListener() {
	    @Override
	    public boolean onTouch(View v, MotionEvent event) {
	        if(event.getAction() == MotionEvent.ACTION_DOWN) {
	            bt.sendString("d");
	            return true;
	        } else if (event.getAction() == MotionEvent.ACTION_UP) {
	            bt.sendString("p");
	            return true;
	        }
	        
	        return false;
	    }
	};
	
	OnClickListener radioBtnControlClick = new OnClickListener() {
	    @Override
	    public void onClick(View v) {
	    	bt.sendString("p");
	    }
	};
	
	OnClickListener radioBtnLineaClick = new OnClickListener() {
	    @Override
	    public void onClick(View v) {
	    	bt.sendString("l");
	    }
	};
	
	OnClickListener radioBtnLuzClick = new OnClickListener() {
	    @Override
	    public void onClick(View v) {
	    	bt.sendString("o");
	    }
	};
	
	OnClickListener closeClick = new OnClickListener() {
		public void onClick(View v) {
			bt.close();
		}
	};
	
	OnClickListener connectClick = new OnClickListener() {
		public void onClick(View e) {
			boolean result = bt.connectDevice();
			if (!result) {
				Toast.makeText(getBaseContext(), "Imposible conectar", Toast.LENGTH_LONG).show();
				return;
			}
		}
	};
	
	OnClickListener activateClick = new OnClickListener() {
		public void onClick(View v) {
			lblStatus.setText("Activando...");
			
			// Comprueba que el Bluetooth esté soportado
			if (!bt.isSupported()) {
				Log.d(TAG, "Bluetooth no soportado");
				Toast.makeText(getBaseContext(), "Bluetooth no soportado", Toast.LENGTH_LONG).show();
				return;
			}
			
			// Intenta habilitar el Bluetooth
			boolean result = bt.enableBluetooth();
			if (!result) {
		        // Le pide al usuario que habilite el Bluetooth
		        Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
		        startActivityForResult(enableBtIntent, 1);
		        
		        if (!bt.enableBluetooth()) {
		        	Log.d(TAG, "Imposible activar blueooth");
		        	Toast.makeText(getBaseContext(), "Imposible habilitar Bluetooth", Toast.LENGTH_LONG).show();
		        	return;
		        }
			}
			
			Log.d(TAG, "Bluetooth activado");
		}
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		btnW        = (Button)findViewById(R.id.btnArriba);
		btnD        = (Button)findViewById(R.id.btnDerecha);
		btnA        = (Button)findViewById(R.id.btnIzquierda);
		btnS        = (Button)findViewById(R.id.btnAbajo);
		btnConnect  = (Button)findViewById(R.id.btnConnect);
		btnActivate = (Button)findViewById(R.id.btnActivate);
		btnClose    = (Button)findViewById(R.id.btnClose);
		radioBtnControl = (RadioButton)findViewById(R.id.radioBtnControl);
		radioBtnLinea   = (RadioButton)findViewById(R.id.radioBtnLinea);
		radioBtnLuz     = (RadioButton)findViewById(R.id.radioBtnLuz);
		lblStatus   = (TextView)findViewById(R.id.lblStatus);
		
		btnW.setOnTouchListener(btnWClick);
		btnA.setOnTouchListener(btnAClick);
		btnD.setOnTouchListener(btnDClick);
		btnS.setOnTouchListener(btnSClick);
		btnConnect.setOnClickListener(connectClick);
		btnActivate.setOnClickListener(activateClick);
		btnClose.setOnClickListener(closeClick);
		radioBtnControl.setOnClickListener(radioBtnControlClick);
		radioBtnLinea.setOnClickListener(radioBtnLineaClick);
		radioBtnLuz.setOnClickListener(radioBtnLuzClick);
		
		bt = new BluetoothTransmitter();
	}
	

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
