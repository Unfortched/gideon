/*
 * Сделано в SharpDevelop.
 * Пользователь: Unfortched
 * Дата: 25.09.2016
 * Время: 17:08
 * 
 * Для изменения этого шаблона используйте Сервис | Настройка | Кодирование | Правка стандартных заголовков.
 */
 
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Net;
using System.Net.NetworkInformation;
using System.Linq;
using System.Data;
using System.Text;
using NativeWifi;


namespace TCMIP
{
	/// <summary>
	/// Description of MainForm.
	/// </summary>
	public partial class MainForm : Form
	{
		public MainForm()
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();
			timer1.Start();
			
			foreach( NetworkInterface ni in NetworkInterface.GetAllNetworkInterfaces()){ // цикл для получения информации
																						//о сетевых свойствах компьютера
																						// состоящего из 
																						//трех циклов внутри него
			
				listBox2.Items.Add(ni.Name); // Название сетевого адаптера
				listBox2.Items.Add("MAC:    " + ni.GetPhysicalAddress()); // Его MAC-адрес
				
				foreach( GatewayIPAddressInformation gipi in ni.GetIPProperties().GatewayAddresses ) 
				{
					listBox2.Items.Add( "Gateways:    " + gipi.Address ); // Адрес шлюза
				}
				
				foreach( UnicastIPAddressInformation uipi in ni.GetIPProperties().UnicastAddresses )
				{
					listBox2.Items.Add( "IPv6(4):    "  + uipi.Address + "   Mask:  "  + uipi.IPv4Mask ); // Адрес IP какие 
																										// возможны на этом ПК
				}
			//
			// TODO: Add constructor code after the InitializeComponent() call.
			//
			} 
		}
		
		void Button1Click(object sender, EventArgs e) // событие нажатия на кнопку, операция получения конкретного IP машины
		{   
			string strIP=""; // создаем пустую строку
			System.Net.IPHostEntry host; // создаем объект класса IPHostEntry
			host = System.Net.Dns.GetHostEntry(strIP); // Используем один из методов этого класса, чтобы записать в пустую строку
														// активный IP
			foreach(System.Net.IPAddress ip in host.AddressList) // для каждого объекта ip в найденном списке активных адресов
			{	
				label3.Text=ip.ToString(); // запись адреса в строку
			} 
			
		}
		
		
		void Timer1Tick(object sender, EventArgs e)
		{ int _tick=0;
            	++_tick;	
            	var tcpStatistics = System.Net.NetworkInformation.IPGlobalProperties.GetIPGlobalProperties().GetTcpIPv4Statistics();
            	if (_tick==1)
            	{
            	label1.Text="Received: " + tcpStatistics.SegmentsReceived.ToString() + "Kb";
            	label2.Text="Sent: " + tcpStatistics.SegmentsSent.ToString() + "Kb";      
            	}
		}
		
		void Label4Click(object sender, EventArgs e)
		{
			
		}
		
		void BtnRefreshClick(object sender, EventArgs e) // Событие кнопки для поиска беспроводных сетей и их анализа
		{
			WlanClient client = new WlanClient(); // создание объекта client класса WlanClient
 
	foreach (WlanClient.WlanInterface wlanIface in client.Interfaces)
	{
 
		Wlan.WlanAvailableNetwork[] wlanBssEntries = wlanIface.GetAvailableNetworkList( 0 ); // начальное значение для каждой сети 0
		//очищаем листвью, что бы не дублировать найденые сети при повторном нажатии
 
		listNet.Items.Clear();
		foreach (Wlan.WlanAvailableNetwork network in wlanBssEntries)
		{
			// создаём экземпляр элемента листвью
			ListViewItem listItemWiFi = new ListViewItem(); 
 
			// назначаем ему имя нашей первой найденой сети, в конце убираем нулевые символы - Trim((char)0)
			listItemWiFi.Text = System.Text.ASCIIEncoding.ASCII.GetString(network.dot11Ssid.SSID).Trim((char)0);
 
			// узнаеём дополнительную информацию о сети и так же добавляем её в листвью, но уже в наш только что созданый итем.
			listItemWiFi.SubItems.Add(network.wlanSignalQuality.ToString() + "%");
			// качество связи в процентах
			listItemWiFi.SubItems.Add(System.Text.ASCIIEncoding.ASCII.GetString(network.dot11Ssid.SSID).ToString());
				//network.dot11DefaultAuthAlgorithm.ToString().Trim((char)0)); // тип безопасности
			listItemWiFi.SubItems.Add(network.dot11DefaultCipherAlgorithm.ToString().Trim((char)0)); // тип шифрования
 
			//ну и добавляем скомпанованый элемент непосредственно в листвью
			listNet.Items.Add(listItemWiFi);
 
		}
	}
		}
		
		
		
		
		 Ping ping = new Ping();
        List<IPAddress> local=new List<IPAddress>();
        public bool Conect (IPAddress address) // функция подтверждающая что адрес был найден
        {
            try
            {
              PingReply pingrep=ping.Send(address, 200); // отправляем address пакеты с макс.задержкой в 200мс
                if (pingrep.Address != null) // если ответ не пустой
                {
                  local.Add(address); // добавляем address в лист адресов
                  ListViewItem Item = new ListViewItem(address.ToString()); // в контейнер добавляем сам address
                  Item.SubItems.Add(Dns.GetHostByAddress(address).HostName); // его имя
                  listView1.Items.Add(Item);
                    return true; 
                }
                
            }
            catch
            {
 
            }
            return false;
        }
        public List<IPAddress> getIpList(IPAddress beginIP,IPAddress endIP) // функция получения диапазона
        {
            List<IPAddress> list=new List<IPAddress>(); // создаем объект list класса List<IPAddress>
            var beginIParray = beginIP.GetAddressBytes(); // массив байтов
            var endIParray = endIP.GetAddressBytes();
            Array.Reverse(beginIParray); // изменяем порядок элементов на обратный
            Array.Reverse(endIParray);
            var beginIPint = BitConverter.ToInt32(beginIParray,0); // 4 байта с нулевой позиции преобразуются в число
            var endIPint= BitConverter.ToInt32(endIParray,0);
            for (;beginIPint<=endIPint;beginIPint++)
            {
                var IParray = BitConverter.GetBytes(beginIPint); // возвращает число как массив байтов
                Array.Reverse(IParray); // изменем порядок на обратный
                list.Add(new IPAddress(IParray)); // заносим в таблицу
                
            }
            return list;
        }
        public void checkip(string ipdip) // функция проверки правильности ввода диапазона
        {								// изначально вводится одна строка, которая разбивается на две отдельные
            if (ipdip.Contains("-")) // если есть символ "-"
            {
                string ip1=""; // строка для первого Ip
                string ip2 = ""; // строка для второго Ip
                ip1 = ipdip.Substring(0, ipdip.IndexOf("-")); // ip1 это строка с 0 позиции до символа "-"
                ip2 = ipdip.Substring(ipdip.IndexOf("-") + 1, ipdip.Length - ipdip.IndexOf("-")-1); 
                											//ip2 это строка с позиции символа "-" +1 и до конца строки
                try
                {
                    IPAddress ip_1 = IPAddress.Parse(ip1); // преобразует строки в числа со знаком int32
                    IPAddress ip_2 = IPAddress.Parse(ip2);
                    progressBar1.Maximum = getIpList(ip_1, ip_2).Count; // количество ячеек у полоски
                    foreach (IPAddress ip in getIpList(ip_1, ip_2))
                    {
                        Conect(ip); // функция Conect для ip
                        progressBar1.Value++; // увеличиваем полоску на 1 единицу
                    }
                    progressBar1.Value = 0; // иначе не увеличиваем
                }
                catch
                {
                    tbIp.Text = "неверный диапазон"; // пишем неверный диапазон
                }
                
            }
            else
            {
                if (!Conect(IPAddress.Parse(tbIp.Text))) progressBar1.Value = progressBar1.Maximum;
                // если нет подключений, то полоску заполнить, чтобы выйти из цикла
            }
        }
        private void button1_Click(object sender, EventArgs e)
        	
        {
            checkip(tbIp.Text); // запуск функции checkip для строки диапазона
        }
        
        public void info(IPAddress beginIP,IPAddress endIP) // функция информации о сети
        {
            var beginIParray = beginIP.GetAddressBytes(); // массив байтов
            var endIParray = endIP.GetAddressBytes();
           // byte[] broadcastiparray = new byte[4]; // новые массивы
            byte[] ipadressarray = new byte[4];
            byte[] maskarray = new byte[4];
            IPAddress ipadress; // новые переменные
            IPAddress mask;
            //IPAddress broadcast;
            bool end1=false;
            for (int i=0;i<4;i++)
            {
                for (byte bit = 128; bit >= 1; bit /= 2)
                {
                    if(!end1 && (beginIParray[i]&bit)==(endIParray[i]&bit)) // если flase и биты начала и конца совпадают
                    {
                        maskarray[i] |= bit; // то этот бит уходит в маску
                    }
                    else // иначе
                    {
                        end1 = true;
                        maskarray[i] = (byte)(maskarray[i] & ~bit); //этот бит меняется
                    }
                }
                ipadressarray[i] = (byte)(maskarray[i] & beginIParray[i]); // одинаковые биты маски и начального адреса
                //broadcastiparray[i] = (byte)(~maskarray[i] | ipadressarray[i]); // обратные биты маски к начальному адресу
               
            }

            mask = new IPAddress(maskarray); // вывод свойств на экран
           // broadcast = new IPAddress(broadcastiparray);
            ipadress = new IPAddress(ipadressarray);
            labIP.Text = "IP address: " + ipadress.ToString();
            labMask.Text = "Mask: " + mask.ToString();
           // labBrIp.Text = "Broadcast IP address: " + broadcast.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            info(local.First(), local.Last()); // информация о сети
        }
		
		void Button3Click(object sender, EventArgs e) // Событие нажатия кнопки для утилиты ping
		{
			Ping pingSender = new Ping(); // создаем объект класса pingSender
				PingReply reply = pingSender.Send("yandex.ru"); // создаем переменную reply для применения метода
																// позволяющего отправить пакеты по указанному адресу
			if(reply.Status == IPStatus.Success) // если пакеты дошли до назначения и обратно
			{   
				listBox1.Items.Add("Address: " + reply.Address.ToString() + "      RoundTrip time: " + reply.RoundtripTime);
				//пишет в форме название сайта и задержку соединения с ним
			}
			else {listBox1.Items.Add(reply.Status);	// иначе добавить что пакет не дошел до назначения	
			}
		}
   }
	
}	
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			/*WlanClient client = new WlanClient();                           список вай-фай устройств
 
	foreach (WlanClient.WlanInterface wlanIface in client.Interfaces)
	{
 
		Wlan.WlanAvailableNetwork[] wlanBssEntries = wlanIface.GetAvailableNetworkList( 0 );
 
		//очищаем листвью, что бы не дублировать найденые сети при повторном нажатии
 
		listBox1.Items.Clear();
		foreach (Wlan.WlanAvailableNetwork network in wlanBssEntries)
		{
			// создаём экземпляр элемента листвью
			ListViewItem listItemWiFi = new ListViewItem(); 
 
			// назначаем ему имя нашей первой найденой сети, в конце убираем нулевые символы - Trim((char)0)
			listBox1.Text = System.Text.ASCIIEncoding.ASCII.GetString(network.dot11Ssid.SSID).Trim((char)0);
 
			// узнаеём дополнительную информацию о сети и так же добавляем её в листвью, но уже в наш только что созданый итем.
			listBox1.Items.Add(network.wlanSignalQuality.ToString() + "%"); // качество связи в процентах
			listBox1.Items.Add(network.dot11DefaultAuthAlgorithm.ToString().Trim((char)0)); // тип безопасности
			listBox1.Items.Add(network.dot11DefaultCipherAlgorithm.ToString().Trim((char)0)); // тип шифрования
 
			//ну и добавляем скомпанованый элемент непосредственно в листвью
			listBox1.Items.Add(listItemWiFi);
 
		}
	}
			
			
			/*string strIP="";
			System.Net.IPHostEntry host;
			host = System.Net.Dns.GetHostEntry(strIP);
			foreach(System.Net.IPAddress ip in host.AddressList)
			{
				MessageBox.Show(ip.ToString());
			}
			
			
			Ping pingSender = new Ping();
			
			PingReply reply = pingSender.Send("yandex.ru");
			
			if(reply.Status == IPStatus.Success)
			{
				listBox1.Items.Add("Address: " + reply.Address.ToString());
				listBox1.Items.Add("RoundTrip time: " + reply.RoundtripTime);
			}
			else {listBox1.Items.Add(reply.Status);} */
	//}
 //  }
//}