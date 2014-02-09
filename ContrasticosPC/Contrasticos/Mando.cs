using System;
using System.IO.Ports;
using System.Windows.Forms;

namespace Contrasticos
{
	public class Mando
	{
		private SerialPort port;
		
		public Mando(string portName)
		{
			this.port = new SerialPort(portName);
		}
		
		public bool IsConnected {
			get { return this.port.IsOpen; }
		}
		
		public void Connect()
		{
			try {
				this.port.Open();
			} catch (Exception ex) {
				MessageBox.Show("Imposible conectar\n" + ex.Message, "ERROL SEÑOL", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
		
		public void Disconnect()
		{
			try {
				this.port.Close();
			} catch (Exception ex) {
				MessageBox.Show("Imposible desconectar\n" + ex.Message, "ERROL SEÑOL", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
		
		public void Stop()
		{
			try {
				this.port.Write("p");
			} catch (Exception ex) {
				MessageBox.Show("Error al enviar comando\n" + ex.Message, "ERROL SEÑOL", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
		
		public void LightFollower()
		{
			try {
				this.port.Write("o");
			} catch (Exception ex) {
				MessageBox.Show("Error al enviar comando\n" + ex.Message, "ERROL SEÑOL", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
		
		public void LineFollower()
		{
			try {
				this.port.Write("o");
			} catch (Exception ex) {
				MessageBox.Show("Error al enviar comando\n" + ex.Message, "ERROL SEÑOL", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
		
		public void Forward()
		{
			try {
				this.port.Write("w");
			} catch (Exception ex) {
				MessageBox.Show("Error al enviar comando\n" + ex.Message, "ERROL SEÑOL", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
		
		public void Backward()
		{
			try {
				this.port.Write("s");
			} catch (Exception ex) {
				MessageBox.Show("Error al enviar comando\n" + ex.Message, "ERROL SEÑOL", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
		
		public void Left()
		{
			try {
				this.port.Write("a");
			} catch (Exception ex) {
				MessageBox.Show("Error al enviar comando\n" + ex.Message, "ERROL SEÑOL", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
		
		public void Right()
		{
			try {
				this.port.Write("d");
			} catch (Exception ex) {
				MessageBox.Show("Error al enviar comando\n" + ex.Message, "ERROL SEÑOL", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
	}
}
