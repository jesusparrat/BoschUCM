

import java.awt.Color;
import java.util.Random;
import java.util.concurrent.TimeUnit;

import pacman.controllers.PacmanController;
import pacman.game.Constants;
import pacman.game.Constants.MOVE;
import pacman.game.Game;
import pacman.game.GameView;

/*
 * The Class RandomPacMan.
 */
public final class PacManRandom extends PacmanController {
    private Random rnd = new Random();
    private MOVE[] allMoves = MOVE.values();
    private Color[] colours = {Color.RED, Color.PINK, Color.CYAN, Color.YELLOW};
    
    
    @Override
    public MOVE getMove(Game game, long timeDue) {
	    int[] activePowerPills=game.getActivePowerPillsIndices();
	    for(int i=0;i<activePowerPills.length;i++)
	      GameView.addLines(game,Color.CYAN,game.getPacmanCurrentNodeIndex(),activePowerPills[i]);
	   
	    for(Constants.GHOST g: Constants.GHOST.values()) {
	    	int ghost = game.getGhostCurrentNodeIndex(g);
	        int mspacman = game.getPacmanCurrentNodeIndex();
	        if(game.getGhostLairTime(g)<=0)
	    		GameView.addPoints(game,colours[g.ordinal()],game.getShortestPath(ghost,mspacman));
	    }
	    
	    return allMoves[rnd.nextInt(allMoves.length)];
    }
}