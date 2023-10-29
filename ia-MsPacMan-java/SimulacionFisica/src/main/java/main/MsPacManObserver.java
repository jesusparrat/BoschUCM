package main;

import java.util.EnumMap;

import communication.CommunicationManager;
import communication.JAVA_MESSAGE;
import pacman.game.Constants.GHOST;
import pacman.game.Constants.MOVE;
import pacman.game.GameObserver;

public class MsPacManObserver implements GameObserver{
	private MOVE lastPacManMove = MOVE.LEFT;
	
	
	public void pacManMove(MOVE move, boolean inJunction) {
		if((move != lastPacManMove || inJunction) && move != MOVE.NEUTRAL) {
			System.out.println(move);
			lastPacManMove = move;
			
			CommunicationManager.MessageSender.SendMsg(fromMoveToJavaMessagePacMan(move));
			
			while(true) {
				JAVA_MESSAGE msg = CommunicationManager.MessageSender.ReadMsg();
				if(msg == JAVA_MESSAGE.TURN_ENDED) {
					break;
				}
			}
		}
	}

	public void ghostsMove(EnumMap<GHOST, MOVE> moves, EnumMap<GHOST, Boolean> inJunction) {
		//System.out.println("Ghost move");
		//Se ignora ya que no hay robots para los fantasmas de momento
	}
	
	public void gameStarted() {
        CommunicationManager.MessageSender.SendMsg(JAVA_MESSAGE.START);
        System.out.println("Mandamos mensaje de empezar la partida");
	}
	
	private JAVA_MESSAGE fromMoveToJavaMessagePacMan(MOVE move) {
		if(move == MOVE.UP)
			return JAVA_MESSAGE.PAC_MAN_UP;
		else if(move == MOVE.DOWN)
			return JAVA_MESSAGE.PAC_MAN_DOWN;
		else if(move == MOVE.RIGHT)
			return JAVA_MESSAGE.PAC_MAN_RIGHT;
		else if(move == MOVE.LEFT)
			return JAVA_MESSAGE.PAC_MAN_LEFT;
		
		//nunca llegará aquí en teoría
		return JAVA_MESSAGE.PAC_MAN_NEUTRAL;
	}

}

