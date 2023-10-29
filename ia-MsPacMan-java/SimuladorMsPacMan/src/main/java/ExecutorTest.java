

import pacman.Executor;
import pacman.controllers.GhostController;
import pacman.controllers.GhostsRandom;
import pacman.controllers.HumanController;
import pacman.controllers.KeyBoardInput;
import pacman.controllers.PacmanController;
import pacman.game.internal.POType;


public class ExecutorTest {

    public static void main(String[] args) {
        Executor executor = new Executor.Builder()
                .setTickLimit(4000)
                .setTimeLimit(40)
                .setGhostPO(false)
                .setPacmanPO(false)
                .setPacmanPOvisual(false) 
                .setPOType(POType.LOS)
                .setVisual(true)
                .setScaleFactor(3.0)
                .build();

        PacmanController pacMan = new PacManRandom();
        						//new HumanController(new KeyBoardInput());
        GhostController ghosts = new GhostsRandom();
        
        System.out.println( 
        		executor.runGame(pacMan, ghosts, 40)
        );
        System.out.println("CERRADO");
        
    }
}

