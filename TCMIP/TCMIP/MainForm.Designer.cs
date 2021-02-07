/*
 * Сделано в SharpDevelop.
 * Пользователь: Unfortched
 * Дата: 25.09.2016
 * Время: 17:08
 * 
 * Для изменения этого шаблона используйте Сервис | Настройка | Кодирование | Правка стандартных заголовков.
 */
namespace TCMIP
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
			this.components = new System.ComponentModel.Container();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.tbIp = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.listBox2 = new System.Windows.Forms.ListBox();
			this.btnInfo = new System.Windows.Forms.Button();
			this.btnRefresh = new System.Windows.Forms.Button();
			this.listNet = new System.Windows.Forms.ListView();
			this.listView1 = new System.Windows.Forms.ListView();
			this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
			this.labIP = new System.Windows.Forms.Label();
			this.labMask = new System.Windows.Forms.Label();
			this.labBrIp = new System.Windows.Forms.Label();
			this.progressBar1 = new System.Windows.Forms.ProgressBar();
			this.button1 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.listBox1 = new System.Windows.Forms.ListBox();
			this.label5 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.button3 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.label1.Location = new System.Drawing.Point(28, 154);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(258, 28);
			this.label1.TabIndex = 1;
			this.label1.Text = "label1";
			this.label1.TextChanged += new System.EventHandler(this.Timer1Tick);
			// 
			// label2
			// 
			this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.label2.Location = new System.Drawing.Point(28, 201);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(218, 30);
			this.label2.TabIndex = 2;
			this.label2.Text = "label2";
			// 
			// timer1
			// 
			this.timer1.Tick += new System.EventHandler(this.Timer1Tick);
			// 
			// tbIp
			// 
			this.tbIp.Location = new System.Drawing.Point(588, 46);
			this.tbIp.Name = "tbIp";
			this.tbIp.Size = new System.Drawing.Size(272, 20);
			this.tbIp.TabIndex = 5;
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(171, 274);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(100, 23);
			this.label3.TabIndex = 11;
			this.label3.Text = "IP";
			// 
			// listBox2
			// 
			this.listBox2.FormattingEnabled = true;
			this.listBox2.Location = new System.Drawing.Point(28, 300);
			this.listBox2.Name = "listBox2";
			this.listBox2.Size = new System.Drawing.Size(287, 199);
			this.listBox2.TabIndex = 12;
			// 
			// btnInfo
			// 
			this.btnInfo.Location = new System.Drawing.Point(785, 458);
			this.btnInfo.Name = "btnInfo";
			this.btnInfo.Size = new System.Drawing.Size(75, 23);
			this.btnInfo.TabIndex = 0;
			this.btnInfo.Text = "Свойства";
			this.btnInfo.UseVisualStyleBackColor = true;
			this.btnInfo.Click += new System.EventHandler(this.Button1Click);
			// 
			// btnRefresh
			// 
			this.btnRefresh.Location = new System.Drawing.Point(588, 458);
			this.btnRefresh.Name = "btnRefresh";
			this.btnRefresh.Size = new System.Drawing.Size(75, 23);
			this.btnRefresh.TabIndex = 13;
			this.btnRefresh.Text = "Поиск сетей";
			this.btnRefresh.UseVisualStyleBackColor = true;
			this.btnRefresh.Click += new System.EventHandler(this.BtnRefreshClick);
			// 
			// listNet
			// 
			this.listNet.Location = new System.Drawing.Point(361, 300);
			this.listNet.Name = "listNet";
			this.listNet.Size = new System.Drawing.Size(185, 199);
			this.listNet.TabIndex = 14;
			this.listNet.UseCompatibleStateImageBehavior = false;
			// 
			// listView1
			// 
			this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.columnHeader1,
									this.columnHeader2});
			this.listView1.Location = new System.Drawing.Point(588, 87);
			this.listView1.Name = "listView1";
			this.listView1.Size = new System.Drawing.Size(272, 180);
			this.listView1.TabIndex = 15;
			this.listView1.UseCompatibleStateImageBehavior = false;
			this.listView1.View = System.Windows.Forms.View.Details;
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "IP";
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "Name";
			// 
			// labIP
			// 
			this.labIP.Location = new System.Drawing.Point(588, 316);
			this.labIP.Name = "labIP";
			this.labIP.Size = new System.Drawing.Size(303, 23);
			this.labIP.TabIndex = 16;
			this.labIP.Text = "IP: ";
			// 
			// labMask
			// 
			this.labMask.Location = new System.Drawing.Point(588, 343);
			this.labMask.Name = "labMask";
			this.labMask.Size = new System.Drawing.Size(290, 23);
			this.labMask.TabIndex = 17;
			this.labMask.Text = "Mask: ";
			// 
			// labBrIp
			// 
			this.labBrIp.Location = new System.Drawing.Point(588, 370);
			this.labBrIp.Name = "labBrIp";
			this.labBrIp.Size = new System.Drawing.Size(303, 23);
			this.labBrIp.TabIndex = 18;
			this.labBrIp.Text = " ";
			// 
			// progressBar1
			// 
			this.progressBar1.Location = new System.Drawing.Point(588, 274);
			this.progressBar1.Name = "progressBar1";
			this.progressBar1.Size = new System.Drawing.Size(272, 23);
			this.progressBar1.TabIndex = 20;
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(785, 396);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 21;
			this.button1.Text = "Проверка диапозона";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(588, 396);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(75, 23);
			this.button2.TabIndex = 22;
			this.button2.Text = "Параметры";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// listBox1
			// 
			this.listBox1.FormattingEnabled = true;
			this.listBox1.Location = new System.Drawing.Point(28, 37);
			this.listBox1.Name = "listBox1";
			this.listBox1.Size = new System.Drawing.Size(243, 82);
			this.listBox1.TabIndex = 23;
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(28, 274);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(78, 23);
			this.label5.TabIndex = 24;
			this.label5.Text = "Свойства ПК:";
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(430, 46);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(152, 23);
			this.label4.TabIndex = 25;
			this.label4.Text = "Укажите диапозон поиска";
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(28, 8);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(287, 23);
			this.label6.TabIndex = 26;
			this.label6.Text = "Проверка подключения к yandex.ru";
			// 
			// label7
			// 
			this.label7.Location = new System.Drawing.Point(361, 274);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(200, 23);
			this.label7.TabIndex = 27;
			this.label7.Text = "Беспроводные сети";
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(290, 37);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(96, 82);
			this.button3.TabIndex = 28;
			this.button3.Text = "Попытка подключения";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new System.EventHandler(this.Button3Click);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(903, 524);
			this.Controls.Add(this.button3);
			this.Controls.Add(this.label7);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.listBox1);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.progressBar1);
			this.Controls.Add(this.labBrIp);
			this.Controls.Add(this.labMask);
			this.Controls.Add(this.labIP);
			this.Controls.Add(this.listView1);
			this.Controls.Add(this.listNet);
			this.Controls.Add(this.btnRefresh);
			this.Controls.Add(this.listBox2);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.tbIp);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.btnInfo);
			this.Name = "MainForm";
			this.Text = "TCMIP";
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.ListBox listBox1;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.ProgressBar progressBar1;
		private System.Windows.Forms.Label labBrIp;
		private System.Windows.Forms.Label labMask;
		private System.Windows.Forms.Label labIP;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.ListView listView1;
		private System.Windows.Forms.ListView listNet;
		private System.Windows.Forms.Button btnRefresh;
		private System.Windows.Forms.ListBox listBox2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox tbIp;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button btnInfo;
	}
}
