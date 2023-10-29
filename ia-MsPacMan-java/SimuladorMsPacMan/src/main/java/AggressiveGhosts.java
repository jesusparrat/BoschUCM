

import java.util.EnumMap;

import pacman.controllers.GhostController;
import pacman.game.Constants.DM;
import pacman.game.Constants.GHOST;
import pacman.game.Constants.MOVE;
import pacman.game.Game;

/*
 * The Class AggressiveGhosts.
 */
public final class AggressiveGhosts extends GhostController {
    private EnumMap<GHOST, MOVE> myMoves = new EnumMap<GHOST, MOVE>(GHOST.class);

    /* (non-Javadoc)
     * @see pacman.controllers.Controller#getMove(pacman.game.Game, long)
     */
    @Override
    public EnumMap<GHOST, MOVE> getMove(Game game, long timeDue) {
        myMoves.clear();

        for (GHOST ghost : GHOST.values())                //for each ghost
        {
            if (game.doesGhostRequireAction(ghost))        //if it requires an action
            {
                    myMoves.put(ghost, game.getApproximateNextMoveTowardsTarget(game.getGhostCurrentNodeIndex(ghost),
                            game.getPacmanCurrentNodeIndex(), game.getGhostLastMoveMade(ghost), DM.PATH));

            }
        }

        return myMoves;
    }
}