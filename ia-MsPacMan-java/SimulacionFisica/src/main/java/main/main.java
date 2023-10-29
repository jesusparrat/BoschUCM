package main;

import java.io.IOException;

import com.fazecast.jSerialComm.SerialPort;

import communication.CommunicationManager;
import communication.JAVA_MESSAGE;
import es.ucm.fdi.ici.c2021.practica3.grupo09.MsPacMan;
import pacman.Executor;
import pacman.controllers.GhostController;
import pacman.controllers.GhostsRandom;
import pacman.controllers.HumanController;
import pacman.controllers.KeyBoardInput;
import pacman.controllers.PacmanController;
import pacman.game.internal.POType;



public class main {	
	
	public static void main(String[] args) throws IOException, InterruptedException{		
		//Se inicializa el arduino
		System.out.println("Vamos a inicializar el arduino");	
		SerialPort sp = SerialPort.getCommPort("/dev/ttyACM0");
		sp.setComPortParameters(9600, 8, 1, 0);
		sp.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING | SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0);
		

		//Abrimos el puerto de comunicación con el arduino
		if(sp.openPort()) {
			System.out.println("Puerto abierto");
			sp.getInputStream().close();			
			//Thread.sleep(2000); //Tiempo para que se inicialice el arduino
		}
		else {
			System.out.println("ERROR: No se pudo abrir el puerto");
			return;
		}
		
		
		CommunicationManager.MessageSender.SetSerialPort(sp);
		
		
		//Se limpia el InputStream por si hay basura de otras ejecuciones
		try {
			sp.getInputStream().close();
		} catch (IOException e1) {
			e1.printStackTrace();
			System.out.println("ERROR: No se ha podido limpiar el InputStream");
		}
		
		boolean start = false;
		
		
		while(!start) {
			CommunicationManager.MessageSender.SendMsg(JAVA_MESSAGE.SYNC_ATTEMP);
			
			if(CommunicationManager.MessageSender.ReadMsg() == JAVA_MESSAGE.SYNC)	
				start = true;			
		}
		

		System.out.println("SINCRONIZADOS");	
		
		
		//Se inicializa el servidor
		System.out.println("Emepzamos el simulador");	
		startExecution();
		
		
		//Cerramos el puerto del arduino
		sp.getInputStream().close(); //limpiamos antes de cerrar para cuando se vuelva a abrir	
		if(sp.closePort()) {
			System.out.println("Puerto cerrado");	
		}
		else {
			System.out.println("ERROR: no se ha podido cerrar el puerto");		
		}
	}
	
	
	
	static void startExecution() {
        Executor executor = new Executor.Builder()
                .setTickLimit(4000)
                .setTimeLimit(200)
                .setGhostPO(false)
                .setPacmanPO(false)
                .setPacmanPOvisual(false) 
                .setPOType(POType.LOS)
                .setVisual(true)
                .setScaleFactor(3.0)
                .build();

        PacmanController pacMan = //new pacman.controllers.examples.PacManRandom();
        						new MsPacMan();
        GhostController ghosts = new GhostsRandom();
        MsPacManObserver observer = new MsPacManObserver();
       
        
        System.out.println( 
        		executor.runGame(pacMan, ghosts, 100, observer)
        );
        System.out.println("CERRADO");    
	}
}
