/*
 * Created by SharpDevelop.
 * User: WindowsUser
 * Date: 08/02/2014
 * Time: 11:15
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace Contrasticos
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.groupControl = new System.Windows.Forms.GroupBox();
			this.btnDown = new System.Windows.Forms.Button();
			this.btnRight = new System.Windows.Forms.Button();
			this.btnLeft = new System.Windows.Forms.Button();
			this.btnUp = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.groupConnection = new System.Windows.Forms.GroupBox();
			this.btnDisconnect = new System.Windows.Forms.Button();
			this.btnConnect = new System.Windows.Forms.Button();
			this.comboPort = new System.Windows.Forms.ComboBox();
			this.lblPort = new System.Windows.Forms.Label();
			this.groupMode = new System.Windows.Forms.GroupBox();
			this.btnStop = new System.Windows.Forms.CheckBox();
			this.label2 = new System.Windows.Forms.Label();
			this.comboMode = new System.Windows.Forms.ComboBox();
			this.groupControl.SuspendLayout();
			this.groupConnection.SuspendLayout();
			this.groupMode.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupControl
			// 
			this.groupControl.Controls.Add(this.btnDown);
			this.groupControl.Controls.Add(this.btnRight);
			this.groupControl.Controls.Add(this.btnLeft);
			this.groupControl.Controls.Add(this.btnUp);
			this.groupControl.Enabled = false;
			this.groupControl.Location = new System.Drawing.Point(213, 12);
			this.groupControl.Name = "groupControl";
			this.groupControl.Size = new System.Drawing.Size(177, 198);
			this.groupControl.TabIndex = 0;
			this.groupControl.TabStop = false;
			this.groupControl.Text = "Control manual";
			// 
			// btnDown
			// 
			this.btnDown.Image = ((System.Drawing.Image)(resources.GetObject("btnDown.Image")));
			this.btnDown.Location = new System.Drawing.Point(62, 136);
			this.btnDown.Name = "btnDown";
			this.btnDown.Size = new System.Drawing.Size(50, 50);
			this.btnDown.TabIndex = 1;
			this.btnDown.UseVisualStyleBackColor = true;
			this.btnDown.MouseDown += new System.Windows.Forms.MouseEventHandler(this.BtnDownMouseDown);
			this.btnDown.MouseUp += new System.Windows.Forms.MouseEventHandler(this.BtnDownMouseUp);
			// 
			// btnRight
			// 
			this.btnRight.Image = ((System.Drawing.Image)(resources.GetObject("btnRight.Image")));
			this.btnRight.Location = new System.Drawing.Point(118, 80);
			this.btnRight.Name = "btnRight";
			this.btnRight.Size = new System.Drawing.Size(50, 50);
			this.btnRight.TabIndex = 2;
			this.btnRight.UseVisualStyleBackColor = true;
			this.btnRight.MouseDown += new System.Windows.Forms.MouseEventHandler(this.BtnRightMouseDown);
			this.btnRight.MouseUp += new System.Windows.Forms.MouseEventHandler(this.BtnRightMouseUp);
			// 
			// btnLeft
			// 
			this.btnLeft.Image = ((System.Drawing.Image)(resources.GetObject("btnLeft.Image")));
			this.btnLeft.Location = new System.Drawing.Point(6, 80);
			this.btnLeft.Name = "btnLeft";
			this.btnLeft.Size = new System.Drawing.Size(50, 50);
			this.btnLeft.TabIndex = 1;
			this.btnLeft.UseVisualStyleBackColor = true;
			this.btnLeft.MouseDown += new System.Windows.Forms.MouseEventHandler(this.BtnLeftMouseDown);
			this.btnLeft.MouseUp += new System.Windows.Forms.MouseEventHandler(this.BtnLeftMouseUp);
			// 
			// btnUp
			// 
			this.btnUp.Image = ((System.Drawing.Image)(resources.GetObject("btnUp.Image")));
			this.btnUp.Location = new System.Drawing.Point(62, 24);
			this.btnUp.Name = "btnUp";
			this.btnUp.Size = new System.Drawing.Size(50, 50);
			this.btnUp.TabIndex = 0;
			this.btnUp.UseVisualStyleBackColor = true;
			this.btnUp.MouseDown += new System.Windows.Forms.MouseEventHandler(this.BtnUpMouseDown);
			this.btnUp.MouseUp += new System.Windows.Forms.MouseEventHandler(this.BtnUpMouseUp);
			// 
			// label1
			// 
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(38, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(153, 17);
			this.label1.TabIndex = 1;
			this.label1.Text = "LOS 4+1 FANTÁSTICOS";
			// 
			// groupConnection
			// 
			this.groupConnection.Controls.Add(this.btnDisconnect);
			this.groupConnection.Controls.Add(this.btnConnect);
			this.groupConnection.Controls.Add(this.comboPort);
			this.groupConnection.Controls.Add(this.lblPort);
			this.groupConnection.Location = new System.Drawing.Point(12, 31);
			this.groupConnection.Name = "groupConnection";
			this.groupConnection.Size = new System.Drawing.Size(195, 88);
			this.groupConnection.TabIndex = 2;
			this.groupConnection.TabStop = false;
			this.groupConnection.Text = "Conexión";
			// 
			// btnDisconnect
			// 
			this.btnDisconnect.Enabled = false;
			this.btnDisconnect.Location = new System.Drawing.Point(99, 46);
			this.btnDisconnect.Name = "btnDisconnect";
			this.btnDisconnect.Size = new System.Drawing.Size(80, 30);
			this.btnDisconnect.TabIndex = 3;
			this.btnDisconnect.Text = "Desconectar";
			this.btnDisconnect.UseVisualStyleBackColor = true;
			this.btnDisconnect.Click += new System.EventHandler(this.BtnDisconnectClick);
			// 
			// btnConnect
			// 
			this.btnConnect.Location = new System.Drawing.Point(6, 46);
			this.btnConnect.Name = "btnConnect";
			this.btnConnect.Size = new System.Drawing.Size(80, 30);
			this.btnConnect.TabIndex = 2;
			this.btnConnect.Text = "Conectar";
			this.btnConnect.UseVisualStyleBackColor = true;
			this.btnConnect.Click += new System.EventHandler(this.BtnConnectClick);
			// 
			// comboPort
			// 
			this.comboPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboPort.FormattingEnabled = true;
			this.comboPort.Location = new System.Drawing.Point(58, 19);
			this.comboPort.Name = "comboPort";
			this.comboPort.Size = new System.Drawing.Size(121, 21);
			this.comboPort.TabIndex = 1;
			// 
			// lblPort
			// 
			this.lblPort.Location = new System.Drawing.Point(6, 21);
			this.lblPort.Name = "lblPort";
			this.lblPort.Size = new System.Drawing.Size(46, 17);
			this.lblPort.TabIndex = 0;
			this.lblPort.Text = "Puerto:";
			// 
			// groupMode
			// 
			this.groupMode.Controls.Add(this.btnStop);
			this.groupMode.Controls.Add(this.label2);
			this.groupMode.Controls.Add(this.comboMode);
			this.groupMode.Enabled = false;
			this.groupMode.Location = new System.Drawing.Point(12, 125);
			this.groupMode.Name = "groupMode";
			this.groupMode.Size = new System.Drawing.Size(193, 85);
			this.groupMode.TabIndex = 3;
			this.groupMode.TabStop = false;
			this.groupMode.Text = "Modo de funcionamiento";
			// 
			// btnStop
			// 
			this.btnStop.Appearance = System.Windows.Forms.Appearance.Button;
			this.btnStop.Location = new System.Drawing.Point(78, 46);
			this.btnStop.Name = "btnStop";
			this.btnStop.Size = new System.Drawing.Size(80, 30);
			this.btnStop.TabIndex = 4;
			this.btnStop.Text = "Parar";
			this.btnStop.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.btnStop.UseVisualStyleBackColor = true;
			this.btnStop.CheckedChanged += new System.EventHandler(this.BtnStopCheckedChanged);
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(6, 23);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(46, 18);
			this.label2.TabIndex = 1;
			this.label2.Text = "Modo:";
			// 
			// comboMode
			// 
			this.comboMode.DisplayMember = "Manual";
			this.comboMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboMode.FormattingEnabled = true;
			this.comboMode.Items.AddRange(new object[] {
									"Manual",
									"Sigue línea"});
			this.comboMode.Location = new System.Drawing.Point(58, 19);
			this.comboMode.Name = "comboMode";
			this.comboMode.Size = new System.Drawing.Size(121, 21);
			this.comboMode.TabIndex = 0;
			this.comboMode.SelectedIndexChanged += new System.EventHandler(this.ComboModeSelectedIndexChanged);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
			this.ClientSize = new System.Drawing.Size(401, 219);
			this.Controls.Add(this.groupMode);
			this.Controls.Add(this.groupConnection);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.groupControl);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.KeyPreview = true;
			this.MaximizeBox = false;
			this.Name = "MainForm";
			this.Text = "Contrasticos";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainFormFormClosing);
			this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainFormKeyDown);
			this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.MainFormKeyUp);
			this.groupControl.ResumeLayout(false);
			this.groupConnection.ResumeLayout(false);
			this.groupMode.ResumeLayout(false);
			this.ResumeLayout(false);
		}
		private System.Windows.Forms.ComboBox comboMode;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.GroupBox groupMode;
		private System.Windows.Forms.Button btnConnect;
		private System.Windows.Forms.Button btnDisconnect;
		private System.Windows.Forms.Label lblPort;
		private System.Windows.Forms.ComboBox comboPort;
		private System.Windows.Forms.GroupBox groupConnection;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.CheckBox btnStop;
		private System.Windows.Forms.Button btnUp;
		private System.Windows.Forms.Button btnLeft;
		private System.Windows.Forms.Button btnRight;
		private System.Windows.Forms.Button btnDown;
		private System.Windows.Forms.GroupBox groupControl;
	}
}
