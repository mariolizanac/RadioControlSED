using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Windows.Forms;

namespace Contrasticos
{
	public partial class MainForm : Form
	{
		private Mando mando;
		
		public MainForm()
		{
			InitializeComponent();

			this.comboPort.Items.AddRange(SerialPort.GetPortNames());
		}
		
		void BtnConnectClick(object sender, EventArgs e)
		{
			if (this.comboPort.SelectedIndex == -1)
				return;
			
			this.mando = new Mando(this.comboPort.Text);
			this.mando.Connect();
			
			if (this.mando.IsConnected) {
				this.comboMode.SelectedIndex = 0;
				this.btnConnect.Enabled    = false;
				this.btnDisconnect.Enabled = true;
				this.groupControl.Enabled  = true;
				this.groupMode.Enabled     = true;
			}
		}
		
		void BtnDisconnectClick(object sender, EventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			this.mando.Stop();
			this.mando.Disconnect();
			this.DisableUI();
		}
		
		void DisableUI()
		{
			this.btnConnect.Enabled    = true;
			this.btnDisconnect.Enabled = false;
			this.groupControl.Enabled  = false;
			this.groupMode.Enabled     = false;
		}
		
		void ComboModeSelectedIndexChanged(object sender, EventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			switch (this.comboMode.Text) {
				case "Manual":
					this.mando.Stop();
					this.groupControl.Enabled = true;
					this.btnStop.Enabled = false;
					break;
					
				case "Sigue línea":
					this.mando.LineFollower();
					this.groupControl.Enabled = false;
					this.btnStop.Enabled = true;
					break;
					
				case "Sigue luz":
					this.mando.LightFollower();
					this.groupControl.Enabled = false;
					this.btnStop.Enabled = true;
					break;
			}
		}
		
		void MainFormFormClosing(object sender, FormClosingEventArgs e)
		{
			if (this.mando != null && this.mando.IsConnected) {
				this.mando.Stop();
				this.mando.Disconnect();
			}
		}
		
		void BtnLeftMouseDown(object sender, MouseEventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			this.mando.Left();
		}
		
		void BtnLeftMouseUp(object sender, MouseEventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			this.mando.Stop();
		}
		
		void BtnUpMouseDown(object sender, MouseEventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			this.mando.Forward();
		}
		
		void BtnUpMouseUp(object sender, MouseEventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			this.mando.Stop();
		}
		
		void BtnRightMouseDown(object sender, MouseEventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			this.mando.Right();
		}
		
		void BtnRightMouseUp(object sender, MouseEventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			this.mando.Stop();
		}
		
		void BtnDownMouseDown(object sender, MouseEventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			this.mando.Backward();
		}
		
		void BtnDownMouseUp(object sender, MouseEventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			this.mando.Stop();
		}
		
		void MainFormKeyDown(object sender, KeyEventArgs e)
		{
			if (this.mando == null || !this.mando.IsConnected)
				return;
			
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			switch (e.KeyCode) {
				case Keys.W:
				case Keys.Up:
					this.mando.Forward();
					break;
					
				case Keys.A:
				case Keys.Left:
					this.mando.Left();
					break;
					
				case Keys.S:
				case Keys.Down:
					this.mando.Backward();
					break;
					
				case Keys.D:
				case Keys.Right:
					this.mando.Right();
					break;
					
				case Keys.P:
					this.mando.Stop();
					break;
			}
		}
		
		void MainFormKeyUp(object sender, KeyEventArgs e)
		{		
			if (this.mando == null || !this.mando.IsConnected)
				return;
			
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			this.mando.Stop();
		}
		
		void BtnStopCheckedChanged(object sender, EventArgs e)
		{
			if (!this.mando.IsConnected) {
				MessageBox.Show("Conexión perdida", "Oh oh...", MessageBoxButtons.OK, MessageBoxIcon.Error);
				this.DisableUI();
				return;
			}
			
			if (this.btnStop.Checked)
				this.mando.Stop();
			else if (this.comboMode.Text == "Sigue línea")
				this.mando.LineFollower();
			else if (this.comboMode.Text == "Sigue luz")
				this.mando.LightFollower();
		}
	}
}
