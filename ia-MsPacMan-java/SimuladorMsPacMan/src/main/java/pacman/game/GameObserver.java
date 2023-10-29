package pacman.game;

import java.util.EnumMap;

import pacman.game.Constants.GHOST;
import pacman.game.Constants.MOVE;

public interface GameObserver {
	public void gameStarted();
	
	public void pacManMove(MOVE move, boolean inJunction);
	public void ghostsMove(EnumMap<GHOST,MOVE> moves, EnumMap<GHOST,Boolean> inJunction);
}
