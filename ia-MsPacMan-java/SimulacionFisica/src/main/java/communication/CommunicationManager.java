package communication;

import java.io.IOException;

import com.fazecast.jSerialComm.SerialPort;

public class CommunicationManager {
	public static class MessageSender{		
				
		static SerialPort sp = null;
		
		public static void SetSerialPort(SerialPort _sp) {
			sp = _sp;
		}
		
		
		public static void SendMsg(JAVA_MESSAGE msg) {
			if(sp != null) {
				try {
					sp.getInputStream().close();			
					sp.getOutputStream().write((byte)msg.ordinal());
					sp.getOutputStream().flush();
				} catch (Exception e) {
					System.out.println("ERROR when sending message to arduino");
					e.printStackTrace();
				}
			}
		}
	
	
		public static JAVA_MESSAGE ReadMsg() {
			try {
				int byteRead = 0;
				byteRead = sp.getInputStream().read();
				if(byteRead < JAVA_MESSAGE.values().length)
				{
					JAVA_MESSAGE msg = JAVA_MESSAGE.values()[byteRead];
					return msg;
				}
					
			} catch(IOException e) {
				System.out.println("ERROR: Ha fallado la lectura de datos");
			}

			return JAVA_MESSAGE.NULL;
		}
	}
}
